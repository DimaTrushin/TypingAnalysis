#ifndef NSAPPLICATION_NSKERNEL_CKEYEVENT_H
#define NSAPPLICATION_NSKERNEL_CKEYEVENT_H

#include "Keyboard/RawKeyEvent.h"

namespace NSApplication {
namespace NSKernel {

class CKeyEvent {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyID = NSKeyboard::CKeyID;
  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CLabelData = NSKeyboard::CLabelData;
  using CKeyTextData = NSKeyboard::CKeyTextData;

public:
  enum EKeyFlags : unsigned short {
    BasicKey = 0,
    AutoRepeat = 1,
  };

  CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID, CLabelData KeyLabel,
            CKeyTextData KeyText, CTime PressingTime,
            EKeyFlags Flags = BasicKey);
  CKeyEvent(const CKeyPressing& PressingEvent, EKeyFlags Flags = BasicKey);

  void setReleasingTime(CTime ReleasingTime);

  bool isSameKey(const CKeyEvent& KeyEvent) const;
  bool isAutoRepeat() const;

  CKeyPosition getPosition() const;
  CKeyID getID() const;
  CLabelData getLabel() const;
  CKeyTextData getText() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  CTime getDuration() const;

private:
  CKeyPosition KeyPosition_;
  CKeyID KeyID_;
  CLabelData KeyLabel_;
  CKeyTextData KeyText_;
  unsigned short Flags_ = 0;
  CTime PressingTime_;
  CTime ReleasingTime_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYEVENT_H
