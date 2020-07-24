#include "KeyIDWin.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

CKeyID CKeyIDWin::make(UINT VKey, USHORT MakeCode, USHORT Flag) {
  UINT WinVK = makeWinVK(VKey, MakeCode, Flag);
  // TO DO
  // Replace numbers with Windows predefined labels
  switch (WinVK) {
  case 0x08:
    return CKeyIDEnum::Backspace;
  case 0x09:
    return CKeyIDEnum::Tab;
  case 0x0d:
    return CKeyIDEnum::Enter;
  case 0x13:
    return CKeyIDEnum::Pause;
  case 0x14:
    return CKeyIDEnum::Capslock;
  case 0x1b:
    return CKeyIDEnum::Esc;
  case 0x20:
    return CKeyIDEnum::Spacebar;
  case 0x21:
    return CKeyIDEnum::PageUp;
  case 0x22:
    return CKeyIDEnum::PageDown;
  case 0x23:
    return CKeyIDEnum::End;
  case 0x24:
    return CKeyIDEnum::Home;
  case 0x25:
    return CKeyIDEnum::LeftArrow;
  case 0x26:
    return CKeyIDEnum::UpArrow;
  case 0x27:
    return CKeyIDEnum::RightArrow;
  case 0x28:
    return CKeyIDEnum::DownArrow;
  case 0x2c:
    return CKeyIDEnum::PrintScreen;
  case 0x2d:
    return CKeyIDEnum::Insert;
  case 0x2e:
    return CKeyIDEnum::Delete;
  case 0x30:
    return CKeyIDEnum::VK_0;
  case 0x31:
    return CKeyIDEnum::VK_1;
  case 0x32:
    return CKeyIDEnum::VK_2;
  case 0x33:
    return CKeyIDEnum::VK_3;
  case 0x34:
    return CKeyIDEnum::VK_4;
  case 0x35:
    return CKeyIDEnum::VK_5;
  case 0x36:
    return CKeyIDEnum::VK_6;
  case 0x37:
    return CKeyIDEnum::VK_7;
  case 0x38:
    return CKeyIDEnum::VK_8;
  case 0x39:
    return CKeyIDEnum::VK_9;
  case 0x41:
    return CKeyIDEnum::A;
  case 0x42:
    return CKeyIDEnum::B;
  case 0x43:
    return CKeyIDEnum::C;
  case 0x44:
    return CKeyIDEnum::D;
  case 0x45:
    return CKeyIDEnum::E;
  case 0x46:
    return CKeyIDEnum::F;
  case 0x47:
    return CKeyIDEnum::G;
  case 0x48:
    return CKeyIDEnum::H;
  case 0x49:
    return CKeyIDEnum::I;
  case 0x4a:
    return CKeyIDEnum::J;
  case 0x4b:
    return CKeyIDEnum::K;
  case 0x4c:
    return CKeyIDEnum::L;
  case 0x4d:
    return CKeyIDEnum::M;
  case 0x4e:
    return CKeyIDEnum::N;
  case 0x4f:
    return CKeyIDEnum::O;
  case 0x50:
    return CKeyIDEnum::P;
  case 0x51:
    return CKeyIDEnum::Q;
  case 0x52:
    return CKeyIDEnum::R;
  case 0x53:
    return CKeyIDEnum::S;
  case 0x54:
    return CKeyIDEnum::T;
  case 0x55:
    return CKeyIDEnum::U;
  case 0x56:
    return CKeyIDEnum::V;
  case 0x57:
    return CKeyIDEnum::W;
  case 0x58:
    return CKeyIDEnum::X;
  case 0x59:
    return CKeyIDEnum::Y;
  case 0x5a:
    return CKeyIDEnum::Z;
  case 0x5b:
    return CKeyIDEnum::LeftWin;
  case 0x5c:
    return CKeyIDEnum::RightWin;
  case 0x5d:
    return CKeyIDEnum::Menu;
  case 0x60:
    return CKeyIDEnum::Numpad_0;
  case 0x61:
    return CKeyIDEnum::Numpad_1;
  case 0x62:
    return CKeyIDEnum::Numpad_2;
  case 0x63:
    return CKeyIDEnum::Numpad_3;
  case 0x64:
    return CKeyIDEnum::Numpad_4;
  case 0x65:
    return CKeyIDEnum::Numpad_5;
  case 0x66:
    return CKeyIDEnum::Numpad_6;
  case 0x67:
    return CKeyIDEnum::Numpad_7;
  case 0x68:
    return CKeyIDEnum::Numpad_8;
  case 0x69:
    return CKeyIDEnum::Numpad_9;
  case 0x6a:
    return CKeyIDEnum::Multiply;
  case 0x6b:
    return CKeyIDEnum::Add;
  case 0x6c:
    return CKeyIDEnum::Separator;
  case 0x6d:
    return CKeyIDEnum::Subtract;
  case 0x6e:
    return CKeyIDEnum::Decimal;
  case 0x6f:
    return CKeyIDEnum::Divide;
  case 0x70:
    return CKeyIDEnum::F1;
  case 0x71:
    return CKeyIDEnum::F2;
  case 0x72:
    return CKeyIDEnum::F3;
  case 0x73:
    return CKeyIDEnum::F4;
  case 0x74:
    return CKeyIDEnum::F5;
  case 0x75:
    return CKeyIDEnum::F6;
  case 0x76:
    return CKeyIDEnum::F7;
  case 0x77:
    return CKeyIDEnum::F8;
  case 0x78:
    return CKeyIDEnum::F9;
  case 0x79:
    return CKeyIDEnum::F10;
  case 0x7a:
    return CKeyIDEnum::F11;
  case 0x7b:
    return CKeyIDEnum::F12;
  case 0x90:
    return CKeyIDEnum::Numlock;
  case 0x91:
    return CKeyIDEnum::Scrolllock;
  case 0xa0:
    return CKeyIDEnum::LeftShift;
  case 0xa1:
    return CKeyIDEnum::RightShift;
  case 0xa2:
    return CKeyIDEnum::LeftCtrl;
  case 0xa3:
    return CKeyIDEnum::RightCtrl;
  case 0xa4:
    return CKeyIDEnum::LeftAlt;
  case 0xa5:
    return CKeyIDEnum::RightAlt;
  case 0xba:
    return CKeyIDEnum::Eng_Semicolon;
  case 0xbb:
    return CKeyIDEnum::Eng_Plus;
  case 0xbc:
    return CKeyIDEnum::Eng_Comma;
  case 0xbd:
    return CKeyIDEnum::Eng_Minus;
  case 0xbe:
    return CKeyIDEnum::Eng_Period;
  case 0xbf:
    return CKeyIDEnum::Eng_Slash_Question;
  case 0xc0:
    return CKeyIDEnum::Eng_Tilde;
  case 0xdb:
    return CKeyIDEnum::Eng_Left_Brace;
  case 0xdc:
    return CKeyIDEnum::Eng_Backslash;
  case 0xdd:
    return CKeyIDEnum::Eng_Right_Brace;
  case 0xde:
    return CKeyIDEnum::Eng_Quote;
  default:
    return CKeyIDEnum::Unknown;
  }
}

UINT CKeyIDWin::makeWinVK(UINT VKey, USHORT MakeCode, USHORT Flag) {
  if (VKey == VK_SHIFT && MakeCode == 0x2a)
    return VK_LSHIFT;
  if (VKey == VK_SHIFT && MakeCode == 0x36)
    return VK_RSHIFT;
  if (VKey == VK_CONTROL && (Flag & RI_KEY_E0) == 0)
    return VK_LCONTROL;
  if (VKey == VK_CONTROL && (Flag & RI_KEY_E0) != 0)
    return VK_RCONTROL;
  if (VKey == VK_MENU && (Flag & RI_KEY_E0) == 0)
    return VK_LMENU;
  if (VKey == VK_MENU && (Flag & RI_KEY_E0) != 0)
    return VK_RMENU;
  return VKey;
}

//UINT CKeyIDWin::makeScanCode(USHORT MakeCode, USHORT Flag) {
//  if (Flag & RI_KEY_E0)
//    return 0xE000 + static_cast<UINT>(MakeCode);
//  if (Flag & RI_KEY_E1)
//    return 0xE100 + static_cast<UINT>(MakeCode);
//  return static_cast<UINT>(MakeCode);
//}


} // NSWindows
} // NSKeyboard
} // NSApplication
