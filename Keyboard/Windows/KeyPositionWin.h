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
  CKeyPosition make(USHORT MakeCode, USHORT Flag);

private:
  CKeyPosition handle69(USHORT Flag) const;
  void update(USHORT MakeCode, USHORT Flag);

  USHORT MakeCodePrevious_ = 0;
  USHORT FlagPrevious_ = 0;
};

} // NSWindows
} // NSKeyboard
} // NSApplication


#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYPOSITIONWIN_H
