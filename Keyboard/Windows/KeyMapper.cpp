#include "KeyMapper.h"

#include <cassert>
#include <stdexcept>

#include "WinKeyboardApi.h"

#include <QDebug>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

namespace NSKeyMapperDetail {

CSimpleKeyMapper::CSimpleKeyMapper(HKL hkl)
  : Layout_(hkl) {
  CWinKeyboardApi::clearOsKeyboardState(Layout_);
  setBaseCharacterTable();
  qDebug() << "Mapper Table size = " << KeyTable_.size();
}

CSimpleKeyMapper::QCharOptional CSimpleKeyMapper::getSymbol(
  CVKCode VK, CKeyShifters Shifters) const {
  auto iter = KeyTable_.find({VK, Shifters});
  if (iter != KeyTable_.cend())
    return iter->second.Character;
  return QCharOptional();
}

bool CSimpleKeyMapper::isDeadKey(CVKCode VK, CKeyShifters Shifters) const {
  auto iter = KeyTable_.find({VK, Shifters});
  if (iter != KeyTable_.cend())
    return iter->second.isDeadKey;
  return false;
}

bool CSimpleKeyMapper::hasSymbol(CVKCode VK, CKeyShifters Shifters) const {
  auto symbOpt = getSymbol(VK, Shifters);
  return symbOpt.has_value();
}

bool CSimpleKeyMapper::isControl(CVKCode VK, CKeyShifters Shifters) const {
  auto symbOpt = getSymbol(VK, Shifters);
  if (!symbOpt.has_value())
    return false;
  return isControl(Shifters, *symbOpt);
}

bool CSimpleKeyMapper::isMapped(CVKCode VK) const {
  for (CKeyShifters Shifters = 0; Shifters < CKeyShiftersEnum::End; ++Shifters)
    if (hasSymbol(VK, Shifters))
      return true;
  return false;
}

HKL CSimpleKeyMapper::getLayout() const {
  return Layout_;
}

bool CSimpleKeyMapper::isControlChar(QChar Char) {
  return (QChar(0x0000) <= Char && Char <= QChar(0x001f))
         || Char == QChar(0x007f)
         || (QChar(0x0080) <= Char && Char <= QChar(0x009f));
  // TO DO
  // Do I need to add this to the list of control chars?
  // \U00A0, \U00AD
}

void CSimpleKeyMapper::setBaseCharacterTable() {
  for (CVKCode VK = 0; VK < CVK::MAX; ++VK)
    if (!isSynthetic(VK))
      handleKey(VK);
}

void CSimpleKeyMapper::handleKey(CVKCode VK) {
  for (CKeyShifters Shifters = 0; Shifters < CKeyShiftersEnum::End; ++Shifters)
    if (!CKeyShiftersEnum::isAltOrShiftAlt(Shifters))
      handleKeyWithShifters(VK, Shifters);
}

void CSimpleKeyMapper::handleKeyWithShifters(CVKCode VK, CKeyShifters Shifters) {
  CWinKeyboardApi::setKeyboardBuffer(Shifters);
  int rc = CWinKeyboardApi::ToUnicodeEx(VK, Layout_);

  if (rc == 0) {
    // ignore
  } else if (rc == 1) {
    // one symbol
    KeyTable_[ {VK, Shifters}] = {CWinKeyboardApi::WBufferPtr()[0], false};
  } else if (rc > 1) {
    // several symbols, ignore
  } else if (rc < 0) {
    // dead key
    KeyTable_[ {VK, Shifters}] = {CWinKeyboardApi::WBufferPtr()[0], true};
  }
  CWinKeyboardApi::clearOsKeyboardState(Layout_);
}

bool CSimpleKeyMapper::isSynthetic(CVKCode VK) const {
  return CWinKeyboardApi::getScanCode(VK, Layout_) == 0;
}


bool CSimpleKeyMapper::isControl(CKeyShifters Shifters, QChar Char) {
  return CKeyShiftersEnum::isCtrlOrShiftCtrl(Shifters) && isControlChar(Char);
}

CKeySequenceMapper::CKeySequenceMapper(HKL Layout) : CBase(Layout) {
  setCompatiblePairs();
  qDebug() << "Mapper PairTable size = " << KeyPairTable_.size();
}

CKeySequenceMapper::QCharOptional CKeySequenceMapper::getCombinedSymbol(
  CVKCode DeadVK,
  CKeyShifters DeadShifters,
  CVKCode VK,
  CKeyShifters Shifters) const {
  auto iter = KeyPairTable_.find({{DeadVK, DeadShifters}, {VK, Shifters}});
  if (iter != KeyPairTable_.cend())
    return iter->second;
  return QCharOptional();
}

bool CKeySequenceMapper::areCompatible(CVKCode DeadVK,
                                       CKeyShifters DeadShifters,
                                       CVKCode VK,
                                       CKeyShifters Shifters) const {
  auto symbOpt = getCombinedSymbol(DeadVK, DeadShifters, VK, Shifters);
  return symbOpt.has_value();
}

void CKeySequenceMapper::setCompatiblePairs() {
  for (auto& KeyPair : KeyTable_) {
    if (KeyPair.second.isDeadKey)
      fillCompatiblePairsForKey(KeyPair.first);
  }
}

void CKeySequenceMapper::fillCompatiblePairsForKey(const CKeyData& DeadKey) {
  for (auto& KeyPair : KeyTable_) {
    if (!KeyPair.second.isDeadKey)
      addIfCompatible(DeadKey,
                      KeyPair.first,
                      KeyPair.second.Character);
  }
}

void CKeySequenceMapper::addIfCompatible(
  const CKeyData& DeadKey,
  const CKeyData& NextKey,
  QChar NextChar) {

  assert(isDeadKey(DeadKey.VK, DeadKey.Shifters));
  assert(!CKeyShiftersEnum::isAltOrShiftAlt(DeadKey.Shifters));

  CWinKeyboardApi::setKeyboardBuffer(DeadKey.Shifters);
  int rc1 = CWinKeyboardApi::ToUnicodeEx(DeadKey.VK, Layout_);

  if (rc1 >= 0)
    throw std::runtime_error("Windows API does not treat a dead key correctly!");

  assert(!CKeyShiftersEnum::isAltOrShiftAlt(NextKey.Shifters));

  CWinKeyboardApi::setKeyboardBuffer(NextKey.Shifters);
  int rc2 = CWinKeyboardApi::ToUnicodeEx(NextKey.VK, Layout_);

  if (rc2 == 1) {
    // This is a compatible case
    QChar CombinedChar = CWinKeyboardApi::WBufferPtr()[0];
    if (!(isControl(NextKey.Shifters, NextChar) || NextChar == CombinedChar)) {
      // NextKey is not a control character
      KeyPairTable_[std::make_pair(DeadKey, NextKey)] = CombinedChar;
    }
  }
  CWinKeyboardApi::clearOsKeyboardState(Layout_);
}

} // NSKeyMapperDetail
} // NSWindows
} // NSKeyboard
} // NSApplication
