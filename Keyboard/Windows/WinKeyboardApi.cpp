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

size_t CWinKeyboardApi::WBufferSize() {
  return getBuffer().size();
}

void CWinKeyboardApi::clearWBuffer() {
  std::fill(getBuffer().begin(), getBuffer().end(), 0);
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
  return ::MapVirtualKeyEx(VK, 0, Layout);
}

std::vector<HKL> CWinKeyboardApi::getSystemLayouts() {
  int NumberOfLayouts = ::GetKeyboardLayoutList(0, NULL);
  if (NumberOfLayouts == 0)
    throw std::runtime_error("Cannot find any Keyboard Layouts!");

  std::vector<HKL> Layouts(NumberOfLayouts);
  int NumberOfWrittenLayouts =
    ::GetKeyboardLayoutList(Layouts.size(), Layouts.data());

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
