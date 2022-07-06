#include "LabelMaker.h"

namespace NSApplication {
namespace NSKeyboard {

CLabelData CLabelMaker::make(CKeyID Key) {
  switch (Key) {
  case CKeyIDEnum::Backspace:
    return {QChar(0x232B), QChar(), 1};
  case CKeyIDEnum::Tab:
    return {QChar(0x2b7e), QChar(), 1};
  case CKeyIDEnum::Enter:
    //    return {QChar(0x2ba0), QChar(), 1};
    return {QChar(0x23ce), QChar(), 1};
  case CKeyIDEnum::Pause:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Capslock:
    return {QChar(0x2B89), QChar(), 1};
  case CKeyIDEnum::Esc:
    return {QChar(0x2bbe), QChar(), 1};
  case CKeyIDEnum::Spacebar:
    return {QChar(0x2423), QChar(), 1};
  case CKeyIDEnum::PageUp:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::PageDown:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::End:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Home:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::LeftArrow:
    return {QChar(0x2190), QChar(), 1};
  case CKeyIDEnum::UpArrow:
    return {QChar(0x2191), QChar(), 1};
  case CKeyIDEnum::RightArrow:
    return {QChar(0x2192), QChar(), 1};
  case CKeyIDEnum::DownArrow:
    return {QChar(0x2193), QChar(), 1};
  case CKeyIDEnum::PrintScreen:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Insert:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Delete:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_0:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_1:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_2:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_3:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_4:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_5:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_6:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_7:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_8:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::VK_9:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::A:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::B:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::C:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::D:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::E:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::G:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::H:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::I:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::J:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::K:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::L:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::M:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::N:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::O:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::P:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Q:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::R:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::S:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::T:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::U:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::V:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::W:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::X:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Y:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Z:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::LeftWin:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::RightWin:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Menu:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_0:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_1:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_2:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_3:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_4:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_5:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_6:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_7:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_8:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numpad_9:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Multiply:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Add:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Separator:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Subtract:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Decimal:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Divide:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F1:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F2:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F3:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F4:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F5:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F6:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F7:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F8:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F9:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F10:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F11:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::F12:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Numlock:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Scrolllock:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::LeftShift:
    return {QChar(0x2B01), QChar(), 1};
  case CKeyIDEnum::RightShift:
    return {QChar(0x2B00), QChar(), 1};
  case CKeyIDEnum::LeftCtrl:
    return {QChar(0x2343), QChar(), 1};
  case CKeyIDEnum::RightCtrl:
    return {QChar(0x2344), QChar(), 1};
  case CKeyIDEnum::LeftAlt:
    return {QChar(0x2347), QChar(), 1};
  case CKeyIDEnum::RightAlt:
    return {QChar(0x2348), QChar(), 1};
  case CKeyIDEnum::Eng_Semicolon:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Plus:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Comma:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Minus:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Period:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Slash_Question:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Tilde:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Left_Brace:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Backslash:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Right_Brace:
    return {QChar(), QChar(), 0};
  case CKeyIDEnum::Eng_Quote:
    return {QChar(), QChar(), 0};
  default:
    return {QChar(), QChar(), 0};
  }
}

} // namespace NSKeyboard
} // namespace NSApplication
