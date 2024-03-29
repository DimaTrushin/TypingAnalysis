#include "KeyEvent.h"

namespace NSApplication {
namespace NSKernel {

CKeyEvent::CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID,
                     CLabelData KeyLabel, CKeyTextData KeyText,
                     CTime PressingTime, CKeyFlags Flags)
    : KeyPosition_(KeyPosition), KeyID_(KeyID), KeyLabel_(KeyLabel),
      KeyText_(KeyText), Flags_(Flags), PressingTime_(PressingTime),
      ReleasingTime_(PressingTime_) {
}

CKeyEvent::CKeyEvent(const CKeyEvent::CKeyPressing& PressingEvent,
                     CKeyFlags Flags)
    : CKeyEvent(PressingEvent.KeyPosition, PressingEvent.KeyID,
                PressingEvent.KeyLabel, PressingEvent.KeyText,
                PressingEvent.Time, Flags | PressingEvent.Shifters) {
}

void CKeyEvent::setReleasingTime(CTime ReleasingTime) {
  ReleasingTime_ = ReleasingTime;
}

bool CKeyEvent::isSameKey(const CKeyEvent& KeyEvent) const {
  return KeyPosition_ == KeyEvent.KeyPosition_;
}

bool CKeyEvent::isAutoRepeat() const {
  return Flags_ & CKeyFlagsEnum::AutoRepeat;
}

CKeyFlags CKeyEvent::getFlags() const {
  return Flags_;
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

unsigned char CKeyEvent::getTextSize() const {
  return KeyText_.Size;
}

bool CKeyEvent::hasText() const {
  return getTextSize() != 0;
}

QChar CKeyEvent::getSymbol(unsigned char index) const {
  assert(index < KeyText_.Size);
  return KeyText_.Symbol[index];
}

QChar CKeyEvent::getLastSymbol() const {
  assert(KeyText_.Size >= 0);
  return KeyText_.Symbol[KeyText_.Size - 1];
}

QChar CKeyEvent::getRawSymbol() const {
  if (isTrackableSpecial())
    return KeyLabel_.LowSymbol;
  if (KeyText_.Size > 0)
    return getLastSymbol();
  if (KeyLabel_.Size > 0) {
    if ((Flags_ & CKeyFlagsEnum::Shift) && KeyLabel_.Size == 2)
      return KeyLabel_.HighSymbol;
    return KeyLabel_.LowSymbol;
  }
  return QChar();
}

QString CKeyEvent::getText() const {
  return QString(KeyText_.Symbol, KeyText_.Size);
}

bool CKeyEvent::isBackspace() const {
  return KeyID_ == CKeyIDEnum::Backspace;
}

bool CKeyEvent::isEnter() const {
  return KeyID_ == CKeyIDEnum::Enter;
}

bool CKeyEvent::isSpace() const {
  return KeyID_ == CKeyIDEnum::Spacebar;
}

bool CKeyEvent::isTab() const {
  return KeyID_ == CKeyIDEnum::Tab;
}

bool CKeyEvent::isEscape() const {
  return KeyID_ == CKeyIDEnum::Esc;
}

bool CKeyEvent::isControl() const {
  return isShift() || isCtrl() || isAlt() || isCapslock();
}

bool CKeyEvent::isShift() const {
  return KeyID_ == CKeyIDEnum::LeftShift || KeyID_ == CKeyIDEnum::RightShift;
}

bool CKeyEvent::isCtrl() const {
  return KeyID_ == CKeyIDEnum::LeftCtrl || KeyID_ == CKeyIDEnum::RightCtrl;
}

bool CKeyEvent::isAlt() const {
  return KeyID_ == CKeyIDEnum::LeftAlt || KeyID_ == CKeyIDEnum::RightAlt;
}

bool CKeyEvent::isCapslock() const {
  return KeyID_ == CKeyIDEnum::Capslock;
}

bool CKeyEvent::isTrackableSpecial() const {
  return isBackspace() || isEnter() || isSpace() || isTab() || isEscape() ||
         isControl();
}

bool CKeyEvent::isShiftActive() const {
  return CKeyFlagsEnum::Shift & Flags_;
}

bool CKeyEvent::isCtrlActive() const {
  return CKeyFlagsEnum::Ctrl & Flags_;
}

bool CKeyEvent::isAltActive() const {
  return CKeyFlagsEnum::Alt & Flags_;
}

bool CKeyEvent::isCapslockToggled() const {
  return CKeyFlagsEnum::Capslock & Flags_;
}

bool CKeyEvent::isDeadKey() const {
  return CKeyFlagsEnum::DeadKey & Flags_;
}

bool CKeyEvent::isSilentDeadKey() const {
  return isDeadKey() && !hasText();
}

} // namespace NSKernel
} // namespace NSApplication
