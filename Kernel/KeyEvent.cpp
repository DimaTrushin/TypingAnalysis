#include "KeyEvent.h"

namespace NSApplication {
namespace NSKernel {

CKeyEvent::CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID, QChar KeyLabel,
                     QString KeyText, CTime PressingTime)
    : KeyPosition_(KeyPosition), KeyID_(KeyID), KeyLabel_(KeyLabel),
      KeyText_(KeyText), PressingTime_(PressingTime),
      ReleasingTime_(PressingTime_) {
}

CKeyEvent::CKeyEvent(const CKeyEvent::CKeyPressing& PressingEvent)
    : CKeyEvent(PressingEvent.KeyPosition, PressingEvent.KeyID,
                PressingEvent.KeyLabel, PressingEvent.KeyText,
                PressingEvent.Time) {
}

CKeyEvent::CKeyEvent() {
    NSApplication::NSKeyboard::CKeyPosition KeyPosition = NSApplication::NSKeyboard::CKeyPosEnum::ESC;
    NSApplication::NSKeyboard::CKeyID KeyID = NSApplication::NSKeyboard::CKeyIDEnum::Esc;
    QChar KeyLabel = 'a';
    QString KeyText = "a";
    NSApplication::CTime PressingTime = NSApplication::CTime();
    NSApplication::NSKernel::CKeyEvent kevt =
            NSApplication::NSKernel::CKeyEvent(KeyPosition, KeyID, KeyLabel,KeyText, PressingTime);
}

void CKeyEvent::setReleasingTime(CTime ReleasingTime) {
  ReleasingTime_ = ReleasingTime;
}

bool CKeyEvent::isSameKey(const CKeyEvent& KeyEvent) const {
  return KeyPosition_ == KeyEvent.KeyPosition_;
}

CKeyEvent::CKeyPosition CKeyEvent::getPosition() const {
  return KeyPosition_;
}

CKeyEvent::CKeyID CKeyEvent::getID() const {
  return KeyID_;
}

QChar CKeyEvent::getLabel() const {
  return KeyLabel_;
}

QString CKeyEvent::getText() const {
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
