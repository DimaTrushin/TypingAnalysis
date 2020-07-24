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
      result = CKeyPosEnum::KPEN;
      break;
    case 29:
      result = CKeyPosEnum::RCTL;
      break;
    case 53:
      result = CKeyPosEnum::KPDV;
      break;
    case 56:
      result = CKeyPosEnum::RALT;
      break;
    case 71:
      result = CKeyPosEnum::HOME;
      break;
    case 72:
      result = CKeyPosEnum::UP;
      break;
    case 73:
      result = CKeyPosEnum::PGUP;
      break;
    case 75:
      result = CKeyPosEnum::LEFT;
      break;
    case 77:
      result = CKeyPosEnum::RGHT;
      break;
    case 79:
      result = CKeyPosEnum::END;
      break;
    case 80:
      result = CKeyPosEnum::DOWN;
      break;
    case 81:
      result = CKeyPosEnum::PGDN;
      break;
    case 82:
      result = CKeyPosEnum::INS;
      break;
    case 83:
      result = CKeyPosEnum::DELE;
      break;
    case 91:
      result = CKeyPosEnum::LWIN;
      break;
    case 92:
      result = CKeyPosEnum::RWIN;
      break;
    case 93:
      result = CKeyPosEnum::MENU;
      break;
    case 42:
      result = CKeyPosEnum::IGNR;
      break;
    case 55:
      result = CKeyPosEnum::PRSC;
      break;
    default:
      result = CKeyPosEnum::UNKN;
      break;
    }
    update(MakeCode, Flag);
    return result;
  }
  if (hasPrefixE1(Flag)) {
    CKeyPosition result;
    switch (MakeCode) {
    case 29:
      result = CKeyPosEnum::PAUS;
      break;
    default:
      result = CKeyPosEnum::UNKN;
      break;
    }
    update(MakeCode, Flag);
    return result;
  }
  CKeyPosition result;
  switch (MakeCode) {
  case 1:
    result = CKeyPosEnum::ESC;
    break;
  case 2:
    result = CKeyPosEnum::AE01;
    break;
  case 3:
    result = CKeyPosEnum::AE02;
    break;
  case 4:
    result = CKeyPosEnum::AE03;
    break;
  case 5:
    result = CKeyPosEnum::AE04;
    break;
  case 6:
    result = CKeyPosEnum::AE05;
    break;
  case 7:
    result = CKeyPosEnum::AE06;
    break;
  case 8:
    result = CKeyPosEnum::AE07;
    break;
  case 9:
    result = CKeyPosEnum::AE08;
    break;
  case 10:
    result = CKeyPosEnum::AE09;
    break;
  case 11:
    result = CKeyPosEnum::AE10;
    break;
  case 12:
    result = CKeyPosEnum::AE11;
    break;
  case 13:
    result = CKeyPosEnum::AE12;
    break;
  case 14:
    result = CKeyPosEnum::BKSP;
    break;
  case 15:
    result = CKeyPosEnum::TAB;
    break;
  case 16:
    result = CKeyPosEnum::AD01;
    break;
  case 17:
    result = CKeyPosEnum::AD02;
    break;
  case 18:
    result = CKeyPosEnum::AD03;
    break;
  case 19:
    result = CKeyPosEnum::AD04;
    break;
  case 20:
    result = CKeyPosEnum::AD05;
    break;
  case 21:
    result = CKeyPosEnum::AD06;
    break;
  case 22:
    result = CKeyPosEnum::AD07;
    break;
  case 23:
    result = CKeyPosEnum::AD08;
    break;
  case 24:
    result = CKeyPosEnum::AD09;
    break;
  case 25:
    result = CKeyPosEnum::AD10;
    break;
  case 26:
    result = CKeyPosEnum::AD11;
    break;
  case 27:
    result = CKeyPosEnum::AD12;
    break;
  case 28:
    result = CKeyPosEnum::RTRN;
    break;
  case 29:
    result = CKeyPosEnum::LCTL;
    break;
  case 30:
    result = CKeyPosEnum::AC01;
    break;
  case 31:
    result = CKeyPosEnum::AC02;
    break;
  case 32:
    result = CKeyPosEnum::AC03;
    break;
  case 33:
    result = CKeyPosEnum::AC04;
    break;
  case 34:
    result = CKeyPosEnum::AC05;
    break;
  case 35:
    result = CKeyPosEnum::AC06;
    break;
  case 36:
    result = CKeyPosEnum::AC07;
    break;
  case 37:
    result = CKeyPosEnum::AC08;
    break;
  case 38:
    result = CKeyPosEnum::AC09;
    break;
  case 39:
    result = CKeyPosEnum::AC10;
    break;
  case 40:
    result = CKeyPosEnum::AC11;
    break;
  case 41:
    result = CKeyPosEnum::TLDE;
    break;
  case 42:
    result = CKeyPosEnum::LFSH;
    break;
  case 43:
    result = CKeyPosEnum::BKSL;
    break;
  case 44:
    result = CKeyPosEnum::AB01;
    break;
  case 45:
    result = CKeyPosEnum::AB02;
    break;
  case 46:
    result = CKeyPosEnum::AB03;
    break;
  case 47:
    result = CKeyPosEnum::AB04;
    break;
  case 48:
    result = CKeyPosEnum::AB05;
    break;
  case 49:
    result = CKeyPosEnum::AB06;
    break;
  case 50:
    result = CKeyPosEnum::AB07;
    break;
  case 51:
    result = CKeyPosEnum::AB08;
    break;
  case 52:
    result = CKeyPosEnum::AB09;
    break;
  case 53:
    result = CKeyPosEnum::AB10;
    break;
  case 54:
    result = CKeyPosEnum::RTSH;
    break;
  case 55:
    result = CKeyPosEnum::KPMU;
    break;
  case 56:
    result = CKeyPosEnum::LALT;
    break;
  case 57:
    result = CKeyPosEnum::SPCE;
    break;
  case 58:
    result = CKeyPosEnum::CAPS;
    break;
  case 59:
    result = CKeyPosEnum::FK01;
    break;
  case 60:
    result = CKeyPosEnum::FK02;
    break;
  case 61:
    result = CKeyPosEnum::FK03;
    break;
  case 62:
    result = CKeyPosEnum::FK04;
    break;
  case 63:
    result = CKeyPosEnum::FK05;
    break;
  case 64:
    result = CKeyPosEnum::FK06;
    break;
  case 65:
    result = CKeyPosEnum::FK07;
    break;
  case 66:
    result = CKeyPosEnum::FK08;
    break;
  case 67:
    result = CKeyPosEnum::FK09;
    break;
  case 68:
    result = CKeyPosEnum::FK10;
    break;
  case 69:
    result = handle69(Flag);
    break;
  case 70:
    result = CKeyPosEnum::SCLK;
    break;
  case 71:
    result = CKeyPosEnum::KP7;
    break;
  case 72:
    result = CKeyPosEnum::KP8;
    break;
  case 73:
    result = CKeyPosEnum::KP9;
    break;
  case 74:
    result = CKeyPosEnum::KPSU;
    break;
  case 75:
    result = CKeyPosEnum::KP4;
    break;
  case 76:
    result = CKeyPosEnum::KP5;
    break;
  case 77:
    result = CKeyPosEnum::KP6;
    break;
  case 78:
    result = CKeyPosEnum::KPAD;
    break;
  case 79:
    result = CKeyPosEnum::KP1;
    break;
  case 80:
    result = CKeyPosEnum::KP2;
    break;
  case 81:
    result = CKeyPosEnum::KP3;
    break;
  case 82:
    result = CKeyPosEnum::kP0;
    break;
  case 83:
    result = CKeyPosEnum::kPDL;
    break;
  case 87:
    result = CKeyPosEnum::FK11;
    break;
  case 88:
    result = CKeyPosEnum::FK12;
    break;
  default:
    result = CKeyPosEnum::UNKN;
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
    return CKeyPosEnum::IGNR;
  if (isReleasing(Flag) && MakeCodePrevious_ == 29 && FlagPrevious_ == 5)
    return CKeyPosEnum::IGNR;
  return CKeyPosEnum::NMLK;
}

void CKeyPositionWin::update(USHORT MakeCode, USHORT Flag) {
  MakeCodePrevious_ = MakeCode;
  FlagPrevious_ = Flag;
}

} // NSWindows
} // NSKeyboard
} // NSApplication
