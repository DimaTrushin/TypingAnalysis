#include "SeanceMaker.h"

namespace NSApplication {
namespace NSKernel {

void CSeanceMaker::add(const CKeyPressing& KeyPressing) {
  assert(LastEvent_ <= KeyPressing.Time);
  if (needNewSession(KeyPressing))
    openNewSession();
  CurrentSession().emplace_back(KeyPressing);
  auto It = findKey(KeyPressing.KeyPosition);
  if (It == PressedKeys_.end())
    PressedKeys_.push_back(&CurrentSession().back());
  LastEvent_ = KeyPressing.Time;
}

void CSeanceMaker::add(const CKeyReleasing& KeyReleasing) {
  assert(LastEvent_ <= KeyReleasing.Time);
  auto It = findKey(KeyReleasing.KeyPosition);
  if (It != PressedKeys_.end()) {
    (*It)->setReleasingTime(KeyReleasing.Time);
    PressedKeys_.erase(It);
    LastEvent_ = KeyReleasing.Time;
  }
}

bool CSeanceMaker::needNewSession(const CKeyPressing& KeyPressing) const {
  // TO DO
  // This is a debug verion
  // Need to add an action for this
  if (!PressedKeys_.empty())
    return false;
  if (KeyPressing.Time < Seconds(10))
    return false;
  return true;
}

void CSeanceMaker::openNewSession() {
  assert(PressedKeys_.empty());
  RawSeance_.emplace_back();
}

CSeanceMaker::CPressedKeys::iterator
CSeanceMaker::findKey(CKeyPosition KeyPosition) {
  return std::find_if(PressedKeys_.begin(),
                      PressedKeys_.end(),
  [KeyPosition](CKeyEvent* KeyEvent) {
    return KeyEvent->getPosition() == KeyPosition;
  });
}

CSeanceMaker::CRawSession& CSeanceMaker::CurrentSession() {
  assert(!RawSeance_.empty());
  return RawSeance_.back();
}

} // NSKernel
} // NSApplication
