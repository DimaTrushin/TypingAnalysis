#ifndef NSAPPLICATION_NSKERNEL_CKEYEVENT_H
#define NSAPPLICATION_NSKERNEL_CKEYEVENT_H

#include "Keyboard/RawKeyEvent.h"

namespace NSApplication {
namespace NSKernel {

struct CKeyFlagsEnum {
  using CType = unsigned short;
  enum : CType {
    BasicKey = 0,
    Shift = 1,
    Ctrl = 2,
    ShiftCtrl = Shift | Ctrl,
    Alt = 4,
    ShiftAlt = Shift | Alt,
    CtrlAlt = Ctrl | Alt,
    ShiftCtrlAlt = Shift | Ctrl | Alt,
    Caps = 8,
    CapsShift = Caps | Shift,
    CapsCtrl = Caps | Ctrl,
    CapsShiftCtrl = Caps | Shift | Ctrl,
    CapsAlt = Caps | Alt,
    CapsShiftAlt = Caps | Shift | Alt,
    CapsCtrlAlt = Caps | Ctrl | Alt,
    CapsShiftCtrlAlt = Caps | Shift | Ctrl | Alt,
    AutoRepeat = 512,
  };
};

using CKeyFlags = CKeyFlagsEnum::CType;

class CKeyEvent {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyID = NSKeyboard::CKeyID;
  using CKeyIDEnum = NSKeyboard::CKeyIDEnum;
  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CLabelData = NSKeyboard::CLabelData;
  using CKeyTextData = NSKeyboard::CKeyTextData;

public:
  CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID, CLabelData KeyLabel,
            CKeyTextData KeyText, CTime PressingTime,
            CKeyFlags Flags = CKeyFlagsEnum::BasicKey);
  CKeyEvent(const CKeyPressing& PressingEvent,
            CKeyFlags Flags = CKeyFlagsEnum::BasicKey);

  void setReleasingTime(CTime ReleasingTime);

  bool isSameKey(const CKeyEvent& KeyEvent) const;
  bool isAutoRepeat() const;

  CKeyPosition getPosition() const;
  CKeyID getID() const;
  CLabelData getLabel() const;
  CKeyTextData getTextData() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  CTime getDuration() const;
  unsigned char getTextSize() const;
  bool hasText() const;
  QChar getSymbol(unsigned char index) const;

  bool isBackspace() const;
  bool isEnter() const;
  bool isSpace() const;
  bool isTab() const;
  bool isEscape() const;
  bool isControl() const;
  bool isShift() const;
  bool isCtrl() const;
  bool isAlt() const;
  bool isCapslock() const;

  // This is a key satisfying one of the condition above
  bool isTrackableSpecial() const;

  bool isShiftActive() const;
  bool isCtrlActive() const;
  bool isAltActive() const;
  bool isCapslockToggled() const;

private:
  CKeyPosition KeyPosition_;
  CKeyID KeyID_;
  CLabelData KeyLabel_;
  CKeyTextData KeyText_;
  unsigned short Flags_ = 0;
  CTime PressingTime_;
  CTime ReleasingTime_;
}; // namespace NSKernel

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYEVENT_H
