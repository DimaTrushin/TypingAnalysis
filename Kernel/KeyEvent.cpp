#include "KeyEvent.h"

namespace NSApplication {
namespace NSKernel {

CKeyEvent::CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID,
                     CLabelData KeyLabel, CKeyTextData KeyText,
                     CTime PressingTime, EKeyFlags Flags)
    : KeyPosition_(KeyPosition), KeyID_(KeyID), KeyLabel_(KeyLabel),
      KeyText_(KeyText), Flags_(Flags), PressingTime_(PressingTime),
      ReleasingTime_(PressingTime_) {
}

CKeyEvent::CKeyEvent(const CKeyEvent::CKeyPressing& PressingEvent,
                     EKeyFlags Flags)
    : CKeyEvent(PressingEvent.KeyPosition, PressingEvent.KeyID,
                PressingEvent.KeyLabel, PressingEvent.KeyText,
                PressingEvent.Time, Flags) {
}

void CKeyEvent::setReleasingTime(CTime ReleasingTime) {
  ReleasingTime_ = ReleasingTime;
}

bool CKeyEvent::isSameKey(const CKeyEvent& KeyEvent) const {
  return KeyPosition_ == KeyEvent.KeyPosition_;
}

bool CKeyEvent::isAutoRepeat() const {
  return Flags_ & AutoRepeat;
}

CKeyEvent::CKeyPosition CKeyEvent::getPosition() const {
  return KeyPosition_;
}

CKeyEvent::CKeyID CKeyEvent::getID() const {
  return KeyID_;
}

CKeyEvent::CLabelData CKeyEvent::getLabel() const {
  return KeyLabel_;
}

CKeyEvent::CKeyTextData CKeyEvent::getText() const {
  return KeyText_;
}

CTime CKeyEvent::getPressingTime() const {
  return PressingTime_;
}

CTime CKeyEvent::getReleasingTime() const {
  return ReleasingTime_;
}

CTime CKeyEvent::getDuration() const {
  return ReleasingTime_ - PressingTime_;
}

} // namespace NSKernel
} // namespace NSApplication
