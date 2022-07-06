#include "WinKeyboardApi.h"

#include "VkCode.h"

#include <stdexcept>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

int CWinKeyboardApi::ToUnicodeEx(CVKCode VK, HKL Layout) {
  clearWBuffer();
  return ::ToUnicodeEx(VK, getScanCode(VK, Layout), KeyboardPtr(), WBufferPtr(),
                       WBufferSize(), 0, Layout);
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
  getKeyboardBuffer()[CVK::Shift] =
      (((Shifters & CKeyShiftersEnum::Shift) != 0) ? 0x80 : 0x00);
  getKeyboardBuffer()[CVK::Ctrl] =
      (((Shifters & CKeyShiftersEnum::Ctrl) != 0) ? 0x80 : 0x00);
  getKeyboardBuffer()[CVK::Alt] =
      (((Shifters & CKeyShiftersEnum::Alt) != 0) ? 0x80 : 0x00);
  getKeyboardBuffer()[CVK::Capslock] =
      ((Shifters & CKeyShiftersEnum::Caps) ? 0x01 : 0x00);
}

void CWinKeyboardApi::clearOsKeyboardState(HKL Layout) {
  static constexpr const CKeyboardBuffer Keyboard{};
  wchar_t sb[2];
  int rc = 0;
  constexpr CVKCode VK = CVK::Decimal;
  while (rc != 1) {
    rc = ::ToUnicodeEx(VK, getScanCode(VK, Layout), Keyboard.data(), sb, 2, 0,
                       Layout);
  }
}

USHORT CWinKeyboardApi::getScanCode(CVKCode VK, HKL Layout) {
  return static_cast<USHORT>(::MapVirtualKeyEx(VK, MAPVK_VK_TO_VSC, Layout));
}

// UINT CWinKeyboardApi::makeScanCode(USHORT MakeCode, USHORT Flag) {
//  if (Flag & RI_KEY_E0)
//    return 0xE000 + static_cast<UINT>(MakeCode);
//  if (Flag & RI_KEY_E1)
//    return 0xE100 + static_cast<UINT>(MakeCode);
//  return static_cast<UINT>(MakeCode);
//}

CVKCode CWinKeyboardApi::getVK(USHORT MakeCode, HKL Layout) {
  return static_cast<CVKCode>(
      ::MapVirtualKeyEx(MakeCode, MAPVK_VSC_TO_VK, Layout));
}

CVKCode CWinKeyboardApi::getSymbolVK(USHORT MakeCode, USHORT Flags,
                                     HKL Layout) {
  if ((Flags & RI_KEY_E0) || (Flags & RI_KEY_E1))
    return getVK(MakeCode, Layout);
  switch (MakeCode) {
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
    return getVK(MakeCode, Layout);
  }
}

CVKCode CWinKeyboardApi::distinguishShifters(CVKCode VKey, USHORT MakeCode,
                                             USHORT Flags) {
  if (VKey == VK_SHIFT && MakeCode == 0x2a)
    return VK_LSHIFT;
  if (VKey == VK_SHIFT && MakeCode == 0x36)
    return VK_RSHIFT;
  if (VKey == VK_CONTROL && (Flags & RI_KEY_E0) == 0)
    return VK_LCONTROL;
  if (VKey == VK_CONTROL && (Flags & RI_KEY_E0) != 0)
    return VK_RCONTROL;
  if (VKey == VK_MENU && (Flags & RI_KEY_E0) == 0)
    return VK_LMENU;
  if (VKey == VK_MENU && (Flags & RI_KEY_E0) != 0)
    return VK_RMENU;
  return VKey;
}

bool CWinKeyboardApi::hasPrefixE0(USHORT Flags) {
  return Flags & RI_KEY_E0;
}

bool CWinKeyboardApi::hasPrefixE1(USHORT Flags) {
  return Flags & RI_KEY_E1;
}

bool CWinKeyboardApi::hasPrefix(USHORT Flags) {
  return hasPrefixE0(Flags) || hasPrefixE1(Flags);
}

bool CWinKeyboardApi::isPressing(USHORT Flags) {
  return (Flags & 1) == RI_KEY_MAKE;
}

bool CWinKeyboardApi::isReleasing(USHORT Flags) {
  return (Flags & 1) == RI_KEY_BREAK;
}

std::vector<HKL> CWinKeyboardApi::getSystemLayouts() {
  int NumberOfLayouts = ::GetKeyboardLayoutList(0, NULL);
  if (NumberOfLayouts == 0)
    throw std::runtime_error("Cannot find any Keyboard Layouts!");

  std::vector<HKL> Layouts(NumberOfLayouts);
  int NumberOfWrittenLayouts =
      ::GetKeyboardLayoutList(static_cast<int>(Layouts.size()), Layouts.data());

  if (NumberOfWrittenLayouts != NumberOfLayouts)
    throw std::runtime_error("GetKeyboardLayoutList does not return correct "
                             "number of Keyboard Layouts!");
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
      ::GetWindowThreadProcessId(::GetForegroundWindow(), nullptr));
}

CWinKeyboardApi::CWBuffer& CWinKeyboardApi::getBuffer() {
  static CWBuffer Buffer{};
  return Buffer;
}

CWinKeyboardApi::CKeyboardBuffer& CWinKeyboardApi::getKeyboardBuffer() {
  static CKeyboardBuffer KbBuffer{};
  return KbBuffer;
}

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication
