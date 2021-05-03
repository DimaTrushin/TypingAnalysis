#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYIDWIN_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYIDWIN_H

#include "Keyboard/KeyID.h"
#include "VkCode.h"
#include <Windows.h>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

class CKeyIDWin {
public:
  static CKeyID make(CVKCode VKey, USHORT MakeCode, USHORT Flag);
};

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYIDWIN_H
