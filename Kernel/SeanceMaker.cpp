#include "SeanceMaker.h"

#include "Seance.h"
#include "TimerAccess.h"

#include <QDebug>

namespace NSApplication {
namespace NSKernel {

namespace NSSeanceMakerDetail {

CPressedKeys::iterator CPressedKeys::findKey(CKeyPosition KeyPosition) {
  return std::find_if(begin(), end(), [KeyPosition](CKeyEvent* KeyEvent) {
    assert(KeyEvent);
    return KeyEvent->getPosition() == KeyPosition;
  });
}

} // namespace NSSeanceMakerDetail

void CSeanceMaker::add(const CKeyPressing& KeyPressing) {
  assert(LastEvent_ <= KeyPressing.Time);
  if (needNewSession(KeyPressing))
    openNewSession();
  auto It = PressedKeys_.findKey(KeyPressing.KeyPosition);
  if (It == PressedKeys_.end()) {
    CurrentSession().emplace_back(KeyPressing);
    PressedKeys_.push_back(&CurrentSession().back());
  } else if (isAutoRepeatAllowed(KeyPressing.KeyID)) {
    CurrentSession().emplace_back(KeyPressing, CKeyFlagsEnum::AutoRepeat);
  } else {
    // TO DO
    // This is generaly an issue situation. If this happens,
    // there should be a fix in the listener
    (**It) = KeyPressing;
    assert(false);
  }
  LastEvent_ = KeyPressing.Time;
}

void CSeanceMaker::add(const CKeyReleasing& KeyReleasing) {
  assert(LastEvent_ <= KeyReleasing.Time);
  auto It = PressedKeys_.findKey(KeyReleasing.KeyPosition);
  if (It != PressedKeys_.end()) {
    (*It)->setReleasingTime(KeyReleasing.Time);
    PressedKeys_.erase(It);
    LastEvent_ = KeyReleasing.Time;
  }
}

void CSeanceMaker::resetTimeLimit() {
  TimeLimit_.reset();
}

void CSeanceMaker::setTimeLimit(CTime TimeLimit) {
  assert(TimeLimit >= CTime());
  TimeLimit_ = TimeLimit;
}

CSeanceMaker::CTimeOptional CSeanceMaker::getTimeLimit() const {
  return TimeLimit_;
}

bool CSeanceMaker::transferTo(CSeance* Seance) {
  assert(Seance);
  bool hasNewData = false;
  if (!PressedKeys_.empty())
    releaseAllKeysNow();
  for (auto& RawSession : RawSeance_)
    if (hasText(RawSession)) {
      // TO DO
      // Add filter ignoring small sessions or any other filtering method
      hasNewData = true;
      Seance->emplace_back(RawSession.begin(), RawSession.end());
    }
  RawSeance_.clear();
  RawSeance_.emplace_back();
  assert(PressedKeys_.empty());
  assert(RawSeance_.size() == 1);
  assert(CurrentSession().empty());
  return hasNewData;
}

void CSeanceMaker::releaseAllKeysNow() {
  CTimerAccess Timer;
  CTime Time = Timer->get();
  for (auto KeyEvent : PressedKeys_)
    KeyEvent->setReleasingTime(Time);
  PressedKeys_.clear();
  assert(!RawSeance_.empty());
}

bool CSeanceMaker::needNewSession(const CKeyPressing& KeyPressing) const {
  assert(!RawSeance_.empty());
  if (!PressedKeys_.empty())
    return false;
  if (CurrentSession().empty())
    return false;
  if (!TimeLimit_.has_value() || KeyPressing.Time - LastEvent_ < *TimeLimit_)
    return false;
  return true;
}

void CSeanceMaker::openNewSession() {
  assert(PressedKeys_.empty());
  assert(!CurrentSession().empty());
  RawSeance_.emplace_back();
}

bool CSeanceMaker::isAutoRepeatAllowed(CKeyID KeyID) const {
  using CKeyIDEnum = NSKeyboard::CKeyIDEnum;
  switch (KeyID) {
  case CKeyIDEnum::LeftShift:
  case CKeyIDEnum::RightShift:
  case CKeyIDEnum::LeftAlt:
  case CKeyIDEnum::RightAlt:
  case CKeyIDEnum::LeftCtrl:
  case CKeyIDEnum::RightCtrl:
  case CKeyIDEnum::Capslock:
    return false;
  default:
    return true;
  }
}

CSeanceMaker::CRawSession& CSeanceMaker::CurrentSession() {
  assert(!RawSeance_.empty());
  return RawSeance_.back();
}

const CSeanceMaker::CRawSession& CSeanceMaker::CurrentSession() const {
  assert(!RawSeance_.empty());
  return RawSeance_.back();
}

CSeanceMaker::CIndex CSeanceMaker::getTextLengh(const CRawSession& Session) {
  CIndex size = 0;
  for (const auto& Key : Session) {
    size += Key.getTextSize();
  }
  return size;
}

bool CSeanceMaker::hasText(const CRawSession& Session) {
  return std::any_of(Session.begin(), Session.end(),
                     [](const auto& Key) { return Key.getTextSize() > 0; });
}

} // namespace NSKernel
} // namespace NSApplication
