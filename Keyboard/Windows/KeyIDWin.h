#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYIDWIN_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYIDWIN_H

#include <Windows.h>
#include "Keyboard/KeyID.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

class CKeyIDWin {
public:
  static CKeyID make(UINT VKey, USHORT MakeCode, USHORT Flag);
  static UINT makeWinVK(UINT VKey, USHORT MakeCode, USHORT Flag);
//  static UINT makeScanCode(USHORT MakeCode, USHORT Flag);
};

} // NSWindows
} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYIDWIN_H
