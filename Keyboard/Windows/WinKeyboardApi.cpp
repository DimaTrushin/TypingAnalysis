#include "WinKeyboardApi.h"

#include "VkCode.h"

#include <stdexcept>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

int CWinKeyboardApi::ToUnicodeEx(UINT VK, HKL Layout) {
  clearWBuffer();
  return ::ToUnicodeEx(VK,
                       getScanCode(VK, Layout),
                       KeyboardPtr(),
                       WBufferPtr(),
                       WBufferSize(),
                       0,
                       Layout);
}

BYTE* CWinKeyboardApi::KeyboardPtr() {
  return getKeyboardBuffer().data();
}

wchar_t* CWinKeyboardApi::WBufferPtr() {
  return getBuffer().data();
}

int CWinKeyboardApi::WBufferSize() {
  return static_cast<int>(getBuffer().size());
}

void CWinKeyboardApi::clearWBuffer() {
  std::fill(getBuffer().begin(), getBuffer().end(), wchar_t(0));
}

void CWinKeyboardApi::setKeyboardBuffer(CKeyShifters Shifters) {
  getKeyboardBuffer()[CVK::Shift] = (((Shifters & CKeyShiftersEnum::Shift) != 0) ? 0x80 : 0x00);
  getKeyboardBuffer()[CVK::Ctrl]  = (((Shifters & CKeyShiftersEnum::Ctrl) != 0) ? 0x80 : 0x00);
  getKeyboardBuffer()[CVK::Alt]   = (((Shifters & CKeyShiftersEnum::Alt) != 0) ? 0x80 : 0x00);
  getKeyboardBuffer()[CVK::Capslock] = (Shifters & CKeyShiftersEnum::Caps ? 0x01 : 0x00);

}

void CWinKeyboardApi::clearOsKeyboardState(HKL Layout) {
  static constexpr const CKeyboardBuffer Keyboard{};
  wchar_t sb[2];
  int rc = 0;
  constexpr CVKCode VK = CVK::Decimal;
  while (rc != 1) {
    rc = ::ToUnicodeEx(VK, getScanCode(VK, Layout), Keyboard.data(), sb, 2, 0, Layout);
  }
}

UINT CWinKeyboardApi::getScanCode(UINT VK, HKL Layout) {
  return ::MapVirtualKeyEx(VK, MAPVK_VK_TO_VSC, Layout);
}

UINT CWinKeyboardApi::getVK(UINT SC, HKL Layout) {
  return ::MapVirtualKeyEx(SC, MAPVK_VSC_TO_VK, Layout);
}

UINT CWinKeyboardApi::getSymbolVK(UINT SC, USHORT Flags, HKL Layout) {
  if ((Flags & RI_KEY_E0) || (Flags & RI_KEY_E1))
    return getVK(SC, Layout);
  switch (SC) {
  case 71:
    return CVK::Numpad_7;
  case 72:
    return CVK::Numpad_8;
  case 73:
    return CVK::Numpad_9;
  case 75:
    return CVK::Numpad_4;
  case 76:
    return CVK::Numpad_5;
  case 77:
    return CVK::Numpad_6;
  case 79:
    return CVK::Numpad_1;
  case 80:
    return CVK::Numpad_2;
  case 81:
    return CVK::Numpad_3;
  case 82:
    return CVK::Numpad_0;
  case 83:
    return CVK::Decimal;
  default:
    return getVK(SC, Layout);
  }
}

std::vector<HKL> CWinKeyboardApi::getSystemLayouts() {
  int NumberOfLayouts = ::GetKeyboardLayoutList(0, NULL);
  if (NumberOfLayouts == 0)
    throw std::runtime_error("Cannot find any Keyboard Layouts!");

  std::vector<HKL> Layouts(NumberOfLayouts);
  int NumberOfWrittenLayouts =
    ::GetKeyboardLayoutList(static_cast<int>(Layouts.size()), Layouts.data());

  if (NumberOfWrittenLayouts != NumberOfLayouts)
    throw std::runtime_error("GetKeyboardLayoutList does not return correct number of Keyboard Layouts!");
  return Layouts;
}

CKeyShifters CWinKeyboardApi::getShifters() {
  static CKeyboardBuffer kbBuffer{};
  ::GetKeyboardState(kbBuffer.data());
  CKeyShifters Shifters = CKeyShiftersEnum::Base;
  if (kbBuffer[CVK::Shift] & 0x80)
    Shifters |= CKeyShiftersEnum::Shift;
  if (kbBuffer[CVK::Ctrl] & 0x80)
    Shifters |= CKeyShiftersEnum::Ctrl;
  if (kbBuffer[CVK::Alt] & 0x80)
    Shifters |= CKeyShiftersEnum::Alt;
  if (kbBuffer[CVK::Capslock] & 0x01)
    Shifters |= CKeyShiftersEnum::Caps;
  return Shifters;
}

HKL CWinKeyboardApi::getForegroundLayout() {
  // This workaround is needed for background windows
  return ::GetKeyboardLayout(
           ::GetWindowThreadProcessId(
             ::GetForegroundWindow(), nullptr));
}

CWinKeyboardApi::CWBuffer& CWinKeyboardApi::getBuffer() {
  static CWBuffer Buffer{};
  return Buffer;
}

CWinKeyboardApi::CKeyboardBuffer& CWinKeyboardApi::getKeyboardBuffer() {
  static CKeyboardBuffer KbBuffer{};
  return KbBuffer;
}

} // NSWindows
} // NSKeyboard
} // NSApplication
