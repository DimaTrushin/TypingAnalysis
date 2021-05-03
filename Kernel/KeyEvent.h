#ifndef NSAPPLICATION_NSKERNEL_CKEYEVENT_H
#define NSAPPLICATION_NSKERNEL_CKEYEVENT_H

#include "Keyboard/RawKeyEvent.h"

namespace NSApplication {
namespace NSKernel {

class CKeyEvent {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyID = NSKeyboard::CKeyID;
  using CKeyPressing = NSKeyboard::CKeyPressing;

public:
  CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID, QChar KeyLabel,
            QString KeyText, CTime PressingTime);
  CKeyEvent(const CKeyPressing& PressingEvent);

  void setReleasingTime(CTime ReleasingTime);

  bool isSameKey(const CKeyEvent& KeyEvent) const;

  CKeyPosition getPosition() const;
  CKeyID getID() const;
  QChar getLabel() const;
  QString getText() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  CTime getDuration() const;

private:
  CKeyPosition KeyPosition_;
  CKeyID KeyID_;
  QChar KeyLabel_;
  // unsigned int Flags_;
  QString KeyText_;
  CTime PressingTime_;
  CTime ReleasingTime_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYEVENT_H
