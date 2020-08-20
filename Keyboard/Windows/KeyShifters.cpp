#include "KeyShifters.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

bool CKeyShiftersEnum::isAltOrShiftAlt(CKeyShiftersEnum::CType Shifters) {
  return (Shifters & ShiftCtrlAlt) == Alt ||
         (Shifters & ShiftCtrlAlt) == ShiftAlt;
}

bool CKeyShiftersEnum::isCtrlOrShiftCtrl(CKeyShiftersEnum::CType Shifters) {
  return (Shifters & ShiftCtrlAlt) == Ctrl ||
         (Shifters & ShiftCtrlAlt) == ShiftCtrl;
}

} // NSWindows
} // NSKeyboard
} // NSApplication
