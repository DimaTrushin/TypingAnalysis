#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CWINKEYBOARDAPI_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CWINKEYBOARDAPI_H

#include "KeyShifters.h"

#include <array>
#include <vector>
#include <Windows.h>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

// This class is not thread safe!
class CWinKeyboardApi {
public:
  using CWBuffer = std::array<wchar_t, 10>;
  using CKeyboardBuffer = std::array<BYTE, 256>;

  static int ToUnicodeEx(UINT VK, HKL Layout);

  static BYTE* KeyboardPtr();
  static wchar_t* WBufferPtr();
  static int WBufferSize();

  static void clearWBuffer();
  static void setKeyboardBuffer(CKeyShifters Shifters);

  static void clearOsKeyboardState(HKL Layout);
  static UINT getScanCode(UINT VK, HKL Layout);

  static std::vector<HKL> getSystemLayouts();

  static CKeyShifters getShifters();

  static HKL getForegroundLayout();

private:
  static CWBuffer& getBuffer();
  static CKeyboardBuffer& getKeyboardBuffer();
};

} // NSWindows
} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CWINKEYBOARDAPI_H
