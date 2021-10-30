#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYSHIFTERS_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYSHIFTERS_H

namespace NSApplication {
namespace NSKeyboard {

class CKeyShiftersEnum {
public:
  using CType = unsigned char;
  enum : CType {
    Base = 0,                                     // 0
    Shift = 1,                                    // 1
    Ctrl = 2,                                     // 2
    ShiftCtrl = Shift | Ctrl,                     // 3
    Alt = 4,                                      // 4 -- NOT USED
    ShiftAlt = Shift | Alt,                       // 5 -- NOT USED
    CtrlAlt = Ctrl | Alt,                         // 6
    ShiftCtrlAlt = Shift | Ctrl | Alt,            // 7
    Caps = 8,                                     // 8
    CapsShift = Caps | Shift,                     // 9
    CapsCtrl = Caps | Ctrl,                       // 10
    CapsShiftCtrl = Caps | Shift | Ctrl,          // 11
    CapsAlt = Caps | Alt,                         // 12 -- NOT USED
    CapsShiftAlt = Caps | Shift | Alt,            // 13 -- NOT USED
    CapsCtrlAlt = Caps | Ctrl | Alt,              // 14
    CapsShiftCtrlAlt = Caps | Shift | Ctrl | Alt, // 15
    End = CapsShiftCtrlAlt + 1                    // 16
  };

  static bool isAltOrShiftAlt(CType Shifters);
  static bool isCtrlOrShiftCtrl(CType Shifters);
};

using CKeyShifters = CKeyShiftersEnum::CType;

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYSHIFTERS_H
