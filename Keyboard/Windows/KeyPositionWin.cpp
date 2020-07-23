#include "KeyPositionWin.h"
#include <cassert>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

CKeyPosition CKeyPositionWin::make(USHORT MakeCode, USHORT Flag) {
  // TO DO
  // Rewrite this in the form:
  // 1) UINT ScanCode = getScanCode(MakeCode, Flag);
  // 2) switch(ScanCode) {...}
  if (hasPrefixE0(Flag)) {
    CKeyPosition result;
    switch (MakeCode) {
    case 28:
      result = CKeyPosition::KPEN;
      break;
    case 29:
      result = CKeyPosition::RCTL;
      break;
    case 53:
      result = CKeyPosition::KPDV;
      break;
    case 56:
      result = CKeyPosition::RALT;
      break;
    case 71:
      result = CKeyPosition::HOME;
      break;
    case 72:
      result = CKeyPosition::UP;
      break;
    case 73:
      result = CKeyPosition::PGUP;
      break;
    case 75:
      result = CKeyPosition::LEFT;
      break;
    case 77:
      result = CKeyPosition::RGHT;
      break;
    case 79:
      result = CKeyPosition::END;
      break;
    case 80:
      result = CKeyPosition::DOWN;
      break;
    case 81:
      result = CKeyPosition::PGDN;
      break;
    case 82:
      result = CKeyPosition::INS;
      break;
    case 83:
      result = CKeyPosition::DELE;
      break;
    case 91:
      result = CKeyPosition::LWIN;
      break;
    case 92:
      result = CKeyPosition::RWIN;
      break;
    case 93:
      result = CKeyPosition::MENU;
      break;
    case 42:
      result = CKeyPosition::IGNR;
      break;
    case 55:
      result = CKeyPosition::PRSC;
      break;
    default:
      result = CKeyPosition::UNKN;
      break;
    }
    update(MakeCode, Flag);
    return result;
  }
  if (hasPrefixE1(Flag)) {
    CKeyPosition result;
    switch (MakeCode) {
    case 29:
      result = CKeyPosition::PAUS;
      break;
    default:
      result = CKeyPosition::UNKN;
      break;
    }
    update(MakeCode, Flag);
    return result;
  }
  CKeyPosition result;
  switch (MakeCode) {
  case 1:
    result = CKeyPosition::ESC;
    break;
  case 2:
    result = CKeyPosition::AE01;
    break;
  case 3:
    result = CKeyPosition::AE02;
    break;
  case 4:
    result = CKeyPosition::AE03;
    break;
  case 5:
    result = CKeyPosition::AE04;
    break;
  case 6:
    result = CKeyPosition::AE05;
    break;
  case 7:
    result = CKeyPosition::AE06;
    break;
  case 8:
    result = CKeyPosition::AE07;
    break;
  case 9:
    result = CKeyPosition::AE08;
    break;
  case 10:
    result = CKeyPosition::AE09;
    break;
  case 11:
    result = CKeyPosition::AE10;
    break;
  case 12:
    result = CKeyPosition::AE11;
    break;
  case 13:
    result = CKeyPosition::AE12;
    break;
  case 14:
    result = CKeyPosition::BKSP;
    break;
  case 15:
    result = CKeyPosition::TAB;
    break;
  case 16:
    result = CKeyPosition::AD01;
    break;
  case 17:
    result = CKeyPosition::AD02;
    break;
  case 18:
    result = CKeyPosition::AD03;
    break;
  case 19:
    result = CKeyPosition::AD04;
    break;
  case 20:
    result = CKeyPosition::AD05;
    break;
  case 21:
    result = CKeyPosition::AD06;
    break;
  case 22:
    result = CKeyPosition::AD07;
    break;
  case 23:
    result = CKeyPosition::AD08;
    break;
  case 24:
    result = CKeyPosition::AD09;
    break;
  case 25:
    result = CKeyPosition::AD10;
    break;
  case 26:
    result = CKeyPosition::AD11;
    break;
  case 27:
    result = CKeyPosition::AD12;
    break;
  case 28:
    result = CKeyPosition::RTRN;
    break;
  case 29:
    result = CKeyPosition::LCTL;
    break;
  case 30:
    result = CKeyPosition::AC01;
    break;
  case 31:
    result = CKeyPosition::AC02;
    break;
  case 32:
    result = CKeyPosition::AC03;
    break;
  case 33:
    result = CKeyPosition::AC04;
    break;
  case 34:
    result = CKeyPosition::AC05;
    break;
  case 35:
    result = CKeyPosition::AC06;
    break;
  case 36:
    result = CKeyPosition::AC07;
    break;
  case 37:
    result = CKeyPosition::AC08;
    break;
  case 38:
    result = CKeyPosition::AC09;
    break;
  case 39:
    result = CKeyPosition::AC10;
    break;
  case 40:
    result = CKeyPosition::AC11;
    break;
  case 41:
    result = CKeyPosition::TLDE;
    break;
  case 42:
    result = CKeyPosition::LFSH;
    break;
  case 43:
    result = CKeyPosition::BKSL;
    break;
  case 44:
    result = CKeyPosition::AB01;
    break;
  case 45:
    result = CKeyPosition::AB02;
    break;
  case 46:
    result = CKeyPosition::AB03;
    break;
  case 47:
    result = CKeyPosition::AB04;
    break;
  case 48:
    result = CKeyPosition::AB05;
    break;
  case 49:
    result = CKeyPosition::AB06;
    break;
  case 50:
    result = CKeyPosition::AB07;
    break;
  case 51:
    result = CKeyPosition::AB08;
    break;
  case 52:
    result = CKeyPosition::AB09;
    break;
  case 53:
    result = CKeyPosition::AB10;
    break;
  case 54:
    result = CKeyPosition::RTSH;
    break;
  case 55:
    result = CKeyPosition::KPMU;
    break;
  case 56:
    result = CKeyPosition::LALT;
    break;
  case 57:
    result = CKeyPosition::SPCE;
    break;
  case 58:
    result = CKeyPosition::CAPS;
    break;
  case 59:
    result = CKeyPosition::FK01;
    break;
  case 60:
    result = CKeyPosition::FK02;
    break;
  case 61:
    result = CKeyPosition::FK03;
    break;
  case 62:
    result = CKeyPosition::FK04;
    break;
  case 63:
    result = CKeyPosition::FK05;
    break;
  case 64:
    result = CKeyPosition::FK06;
    break;
  case 65:
    result = CKeyPosition::FK07;
    break;
  case 66:
    result = CKeyPosition::FK08;
    break;
  case 67:
    result = CKeyPosition::FK09;
    break;
  case 68:
    result = CKeyPosition::FK10;
    break;
  case 69:
    result = handle69(Flag);
    break;
  case 70:
    result = CKeyPosition::SCLK;
    break;
  case 71:
    result = CKeyPosition::KP7;
    break;
  case 72:
    result = CKeyPosition::KP8;
    break;
  case 73:
    result = CKeyPosition::KP9;
    break;
  case 74:
    result = CKeyPosition::KPSU;
    break;
  case 75:
    result = CKeyPosition::KP4;
    break;
  case 76:
    result = CKeyPosition::KP5;
    break;
  case 77:
    result = CKeyPosition::KP6;
    break;
  case 78:
    result = CKeyPosition::KPAD;
    break;
  case 79:
    result = CKeyPosition::KP1;
    break;
  case 80:
    result = CKeyPosition::KP2;
    break;
  case 81:
    result = CKeyPosition::KP3;
    break;
  case 82:
    result = CKeyPosition::kP0;
    break;
  case 83:
    result = CKeyPosition::kPDL;
    break;
  case 87:
    result = CKeyPosition::FK11;
    break;
  case 88:
    result = CKeyPosition::FK12;
    break;
  default:
    result = CKeyPosition::UNKN;
    break;
  }
  update(MakeCode, Flag);
  return result;
}

bool CKeyPositionWin::hasPrefixE0(USHORT Flag) const  {
  return Flag & RI_KEY_E0;
}

bool CKeyPositionWin::hasPrefixE1(USHORT Flag) const {
  return Flag & RI_KEY_E1;
}

bool CKeyPositionWin::hasPrefix(USHORT Flag) const {
  return hasPrefixE0(Flag) || hasPrefixE1(Flag);
}

bool CKeyPositionWin::isPressing(USHORT Flag) const {
  return (Flag & 1) == RI_KEY_MAKE;
}

bool CKeyPositionWin::isReleasing(USHORT Flag) const {
  return (Flag & 1) == RI_KEY_BREAK;
}

CKeyPosition CKeyPositionWin::handle69(USHORT Flag) const {
  assert(!hasPrefix(Flag));
  if (isPressing(Flag) && MakeCodePrevious_ == 29 && FlagPrevious_ == 4)
    return CKeyPosition::IGNR;
  if (isReleasing(Flag) && MakeCodePrevious_ == 29 && FlagPrevious_ == 5)
    return CKeyPosition::IGNR;
  return CKeyPosition::NMLK;
}

void CKeyPositionWin::update(USHORT MakeCode, USHORT Flag) {
  MakeCodePrevious_ = MakeCode;
  FlagPrevious_ = Flag;
}

} // NSWindows
} // NSKeyboard
} // NSApplication
