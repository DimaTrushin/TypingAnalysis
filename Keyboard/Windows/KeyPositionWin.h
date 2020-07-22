#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYPOSITIONWIN_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYPOSITIONWIN_H

#include "Keyboard/KeyPosition.h"
#include <Windows.h>


namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

class CKeyPositionWin {
public:
  CKeyPositionWin() = default;
  CKeyPosition make(USHORT ScanCode, USHORT Flag);
private:
  bool hasPrefixE0(USHORT Flag) const;
  bool hasPrefixE1(USHORT Flag) const;
  bool hasPrefix(USHORT Flag) const;
  bool isPressing(USHORT Flag) const;
  bool isReleasing(USHORT Flag) const;

  CKeyPosition handleE042(USHORT Flag) const;

  CKeyPosition handleE129(USHORT Flag) const;
  CKeyPosition handle69(USHORT Flag) const;

  void update(USHORT ScanCode, USHORT Flag);

  USHORT ScanCodePrevious_ = 0;
  USHORT FlagPrevious_ = 0;
};

} // NSWindows
} // NSKeyboard
} // NSApplication


#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYPOSITIONWIN_H
