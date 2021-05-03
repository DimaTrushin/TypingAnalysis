#ifndef NSAPPLICATION_NSKEYBOARD_CKEYID_H
#define NSAPPLICATION_NSKEYBOARD_CKEYID_H

namespace NSApplication {
namespace NSKeyboard {

struct CKeyIDEnum {
  using CType = unsigned char;
  enum : CType {
    Unknown = 0x0,
    Ignore = 0x1,
    // TO DO
    // Make continuous numeration
    // Add OEM_102 Key
    Backspace = 0x08,
    Tab = 0x09,
    Enter = 0x0d,
    Pause = 0x13,
    Capslock = 0x14,
    Esc = 0x1b,
    Spacebar = 0x20,
    PageUp = 0x21,
    PageDown = 0x22,
    End = 0x23,
    Home = 0x24,
    LeftArrow = 0x25,
    UpArrow = 0x26,
    RightArrow = 0x27,
    DownArrow = 0x28,
    PrintScreen = 0x2c,
    Insert = 0x2d,
    Delete = 0x2e,
    VK_0 = 0x30,
    VK_1 = 0x31,
    VK_2 = 0x32,
    VK_3 = 0x33,
    VK_4 = 0x34,
    VK_5 = 0x35,
    VK_6 = 0x36,
    VK_7 = 0x37,
    VK_8 = 0x38,
    VK_9 = 0x39,
    A = 0x41,
    B = 0x42,
    C = 0x43,
    D = 0x44,
    E = 0x45,
    F = 0x46,
    G = 0x47,
    H = 0x48,
    I = 0x49,
    J = 0x4a,
    K = 0x4b,
    L = 0x4c,
    M = 0x4d,
    N = 0x4e,
    O = 0x4f,
    P = 0x50,
    Q = 0x51,
    R = 0x52,
    S = 0x53,
    T = 0x54,
    U = 0x55,
    V = 0x56,
    W = 0x57,
    X = 0x58,
    Y = 0x59,
    Z = 0x5a,
    LeftWin = 0x5b,
    RightWin = 0x5c,
    Menu = 0x5d,
    Numpad_0 = 0x60,
    Numpad_1 = 0x61,
    Numpad_2 = 0x62,
    Numpad_3 = 0x63,
    Numpad_4 = 0x64,
    Numpad_5 = 0x65,
    Numpad_6 = 0x66,
    Numpad_7 = 0x67,
    Numpad_8 = 0x68,
    Numpad_9 = 0x69,
    Multiply = 0x6a,
    Add = 0x6b,
    Separator = 0x6c,
    Subtract = 0x6d,
    Decimal = 0x6e,
    Divide = 0x6f,
    F1 = 0x70,
    F2 = 0x71,
    F3 = 0x72,
    F4 = 0x73,
    F5 = 0x74,
    F6 = 0x75,
    F7 = 0x76,
    F8 = 0x77,
    F9 = 0x78,
    F10 = 0x79,
    F11 = 0x7a,
    F12 = 0x7b,
    Numlock = 0x90,
    Scrolllock = 0x91,
    LeftShift = 0xa0,
    RightShift = 0xa1,
    LeftCtrl = 0xa2,
    RightCtrl = 0xa3,
    LeftAlt = 0xa4,
    RightAlt = 0xa5,
    Eng_Semicolon = 0xba,      // ;:
    Eng_Plus = 0xbb,           // =+
    Eng_Comma = 0xbc,          // ,<
    Eng_Minus = 0xbd,          // -_
    Eng_Period = 0xbe,         // .>
    Eng_Slash_Question = 0xbf, // /?
    Eng_Tilde = 0xc0,          // `~
    Eng_Left_Brace = 0xdb,     // [{
    Eng_Backslash = 0xdc,      // \|
    Eng_Right_Brace = 0xdd,    // ]}
    Eng_Quote = 0xde,          // '"
  };
};

using CKeyID = CKeyIDEnum::CType;

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYID_H
