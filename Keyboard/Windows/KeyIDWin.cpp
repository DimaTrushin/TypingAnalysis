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
    return CKeyID::Backspace;
  case 0x09:
    return CKeyID::Tab;
  case 0x0d:
    return CKeyID::Enter;
  case 0x13:
    return CKeyID::Pause;
  case 0x14:
    return CKeyID::Capslock;
  case 0x1b:
    return CKeyID::Esc;
  case 0x20:
    return CKeyID::Spacebar;
  case 0x21:
    return CKeyID::PageUp;
  case 0x22:
    return CKeyID::PageDown;
  case 0x23:
    return CKeyID::End;
  case 0x24:
    return CKeyID::Home;
  case 0x25:
    return CKeyID::LeftArrow;
  case 0x26:
    return CKeyID::UpArrow;
  case 0x27:
    return CKeyID::RightArrow;
  case 0x28:
    return CKeyID::DownArrow;
  case 0x2c:
    return CKeyID::PrintScreen;
  case 0x2d:
    return CKeyID::Insert;
  case 0x2e:
    return CKeyID::Delete;
  case 0x30:
    return CKeyID::VK_0;
  case 0x31:
    return CKeyID::VK_1;
  case 0x32:
    return CKeyID::VK_2;
  case 0x33:
    return CKeyID::VK_3;
  case 0x34:
    return CKeyID::VK_4;
  case 0x35:
    return CKeyID::VK_5;
  case 0x36:
    return CKeyID::VK_6;
  case 0x37:
    return CKeyID::VK_7;
  case 0x38:
    return CKeyID::VK_8;
  case 0x39:
    return CKeyID::VK_9;
  case 0x41:
    return CKeyID::A;
  case 0x42:
    return CKeyID::B;
  case 0x43:
    return CKeyID::C;
  case 0x44:
    return CKeyID::D;
  case 0x45:
    return CKeyID::E;
  case 0x46:
    return CKeyID::F;
  case 0x47:
    return CKeyID::G;
  case 0x48:
    return CKeyID::H;
  case 0x49:
    return CKeyID::I;
  case 0x4a:
    return CKeyID::J;
  case 0x4b:
    return CKeyID::K;
  case 0x4c:
    return CKeyID::L;
  case 0x4d:
    return CKeyID::M;
  case 0x4e:
    return CKeyID::N;
  case 0x4f:
    return CKeyID::O;
  case 0x50:
    return CKeyID::P;
  case 0x51:
    return CKeyID::Q;
  case 0x52:
    return CKeyID::R;
  case 0x53:
    return CKeyID::S;
  case 0x54:
    return CKeyID::T;
  case 0x55:
    return CKeyID::U;
  case 0x56:
    return CKeyID::V;
  case 0x57:
    return CKeyID::W;
  case 0x58:
    return CKeyID::X;
  case 0x59:
    return CKeyID::Y;
  case 0x5a:
    return CKeyID::Z;
  case 0x5b:
    return CKeyID::LeftWin;
  case 0x5c:
    return CKeyID::RightWin;
  case 0x5d:
    return CKeyID::Menu;
  case 0x60:
    return CKeyID::Numpad_0;
  case 0x61:
    return CKeyID::Numpad_1;
  case 0x62:
    return CKeyID::Numpad_2;
  case 0x63:
    return CKeyID::Numpad_3;
  case 0x64:
    return CKeyID::Numpad_4;
  case 0x65:
    return CKeyID::Numpad_5;
  case 0x66:
    return CKeyID::Numpad_6;
  case 0x67:
    return CKeyID::Numpad_7;
  case 0x68:
    return CKeyID::Numpad_8;
  case 0x69:
    return CKeyID::Numpad_9;
  case 0x6a:
    return CKeyID::Multiply;
  case 0x6b:
    return CKeyID::Add;
  case 0x6c:
    return CKeyID::Separator;
  case 0x6d:
    return CKeyID::Subtract;
  case 0x6e:
    return CKeyID::Decimal;
  case 0x6f:
    return CKeyID::Divide;
  case 0x70:
    return CKeyID::F1;
  case 0x71:
    return CKeyID::F2;
  case 0x72:
    return CKeyID::F3;
  case 0x73:
    return CKeyID::F4;
  case 0x74:
    return CKeyID::F5;
  case 0x75:
    return CKeyID::F6;
  case 0x76:
    return CKeyID::F7;
  case 0x77:
    return CKeyID::F8;
  case 0x78:
    return CKeyID::F9;
  case 0x79:
    return CKeyID::F10;
  case 0x7a:
    return CKeyID::F11;
  case 0x7b:
    return CKeyID::F12;
  case 0x90:
    return CKeyID::Numlock;
  case 0x91:
    return CKeyID::Scrolllock;
  case 0xa0:
    return CKeyID::LeftShift;
  case 0xa1:
    return CKeyID::RightShift;
  case 0xa2:
    return CKeyID::LeftCtrl;
  case 0xa3:
    return CKeyID::RightCtrl;
  case 0xa4:
    return CKeyID::LeftAlt;
  case 0xa5:
    return CKeyID::RightAlt;
  case 0xba:
    return CKeyID::Eng_Semicolon;
  case 0xbb:
    return CKeyID::Eng_Plus;
  case 0xbc:
    return CKeyID::Eng_Comma;
  case 0xbd:
    return CKeyID::Eng_Minus;
  case 0xbe:
    return CKeyID::Eng_Period;
  case 0xbf:
    return CKeyID::Eng_Slash_Question;
  case 0xc0:
    return CKeyID::Eng_Tilde;
  case 0xdb:
    return CKeyID::Eng_Left_Brace;
  case 0xdc:
    return CKeyID::Eng_Backslash;
  case 0xdd:
    return CKeyID::Eng_Right_Brace;
  case 0xde:
    return CKeyID::Eng_Quote;
  default:
    return CKeyID::Unknown;
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
