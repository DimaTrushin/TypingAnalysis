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

CKeyEvent::CKeyTextData CKeyEvent::getTextData() const {
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

int CKeyEvent::getTextSize() const {
  return KeyText_.Size;
}

bool CKeyEvent::hasText() const {
  return getTextSize() != 0;
}

QChar CKeyEvent::getSymbol(int index) const {
  assert(0 <= index && index < KeyText_.Size);
  return KeyText_.Symbol[index];
}

bool CKeyEvent::isBackspace() const {
  return KeyID_ == CKeyIDEnum::Backspace;
}

} // namespace NSKernel
} // namespace NSApplication
