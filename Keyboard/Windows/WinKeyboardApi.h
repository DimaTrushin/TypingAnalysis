#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CWINKEYBOARDAPI_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CWINKEYBOARDAPI_H

#include "KeyShifters.h"
#include "VkCode.h"

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

  static int ToUnicodeEx(CVKCode VK, HKL Layout);

  static BYTE* KeyboardPtr();
  static wchar_t* WBufferPtr();
  static int WBufferSize();

  static void clearWBuffer();
  static void setKeyboardBuffer(CKeyShifters Shifters);

  static void clearOsKeyboardState(HKL Layout);
  static USHORT getScanCode(CVKCode VK, HKL Layout);
  //static UINT makeScanCode(USHORT MakeCode, USHORT Flag);
  static CVKCode getVK(USHORT MakeCode, HKL Layout);
  static CVKCode getSymbolVK(USHORT MakeCode, USHORT Flags, HKL Layout);
  static CVKCode distinguishShifters(CVKCode VKey, USHORT MakeCode, USHORT Flag);

  static bool hasPrefixE0(USHORT Flags);
  static bool hasPrefixE1(USHORT Flags);
  static bool hasPrefix(USHORT Flags);
  static bool isPressing(USHORT Flags);
  static bool isReleasing(USHORT Flags);

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
