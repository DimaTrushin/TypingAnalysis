#include "KeyTextMaker.h"

#include "KeyIDWin.h"
#include "WinKeyboardApi.h"

#include <cassert>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

CKeyTextMaker::CKeyTextMaker() {
  std::vector<HKL> Layouts = CWinKeyboardApi::getSystemLayouts();
  for (const auto hkl : Layouts)
    Mappers_.try_emplace(hkl, hkl);
  CurrentMapperIt_ = Mappers_.begin();
}

size_t CKeyTextMaker::numberOfMappers() const {
  return Mappers_.size();
}

CKeyTextData CKeyTextMaker::getText(CVKCode VK, CKeyShifters Shifters,
                                    HKL Layout) {
  if (isLayoutChanged(Layout))
    switchLayout(Layout);
  return getKeyTextData(VK, Shifters);
}

CLabelData CKeyTextMaker::getLabel(USHORT MakeCode, USHORT Flags, HKL Layout) {
  CVKCode VK = CWinKeyboardApi::getSymbolVK(MakeCode, Flags, Layout);
  VK = CWinKeyboardApi::distinguishShifters(VK, MakeCode, Flags);
  switch (VK) {
  case CVK::Enter:
    return {QChar(0x2ba0), QChar(), 1};
  case CVK::Ctrl:
    return {QChar(0x2353), QChar(), 1};
  case CVK::LeftCtrl:
    return {QChar(0x2343), QChar(), 1};
  case CVK::RightCtrl:
    return {QChar(0x2344), QChar(), 1};
  case CVK::Alt:
    return {QChar(0x2338), QChar(), 1};
  case CVK::LeftAlt:
    return {QChar(0x2347), QChar(), 1};
  case CVK::RightAlt:
    return {QChar(0x2348), QChar(), 1};
  case CVK::Shift:
    return {QChar(0x21E7), QChar(), 1};
  case CVK::LeftShift:
    return {QChar(0x2B01), QChar(), 1};
  case CVK::RightShift:
    return {QChar(0x2B00), QChar(), 1};
  case CVK::Backspace:
    return {QChar(0x232B), QChar(), 1};
  case CVK::Capslock:
    return {QChar(0x2B89), QChar(), 1};
  case CVK::Tab:
    return {QChar(0x2b7e), QChar(), 1};
  case CVK::Esc:
    return {QChar(0x2bbe), QChar(), 1};
  case CVK::Spacebar:
    return {QChar(0x2423), QChar(), 1};
  // TO DO
  // Add the following keys:
  // F1 -- F12, Insert, Delete, Home, End, PageUp, PageDown
  // NumLock, LWinKey, RWinKey, MenuKey, Arrows, PrtScr, ScrollLock, Pause
  default:
    auto symbOpt = Mapper(Layout).getSymbol(VK, CKeyShiftersEnum::Base);
    if (!symbOpt.has_value())
      return {QChar(), QChar(), 0};
    if (!symbOpt->isPrint())
      return {QChar(), QChar(), 0};
    auto symbShiftOpt = Mapper(Layout).getSymbol(VK, CKeyShiftersEnum::Shift);
    if (!symbShiftOpt.has_value() || *symbOpt == *symbShiftOpt)
      return {*symbOpt, QChar(), 1};
    return {*symbOpt, *symbShiftOpt, 2};
  }
}

bool CKeyTextMaker::isDeadKey(CVKCode VK, CKeyShifters Shifters) const {
  return CurrentMapper().isDeadKey(VK, Shifters);
}

bool CKeyTextMaker::isLayoutChanged(HKL Layout) const {
  return Layout != CurrentLayout();
}

void CKeyTextMaker::switchLayout(HKL Layout) {
  PreviousDeadKey_.reset();
  CurrentMapperIt_ = Mappers_.try_emplace(Layout, Layout).first;
}

CKeyTextData CKeyTextMaker::getKeyTextData(CVKCode VK, CKeyShifters Shifters) {
  if (hasDeadKeyInBuffer())
    return getKeyTextDataWithDeadKey(VK, Shifters);
  return getKeyTextDataNoDeadKey(VK, Shifters);
}

CKeyTextData CKeyTextMaker::getKeyTextDataWithDeadKey(CVKCode VK,
                                                      CKeyShifters Shifters) {
  auto symbOpt = getPlainSymbol(VK, Shifters);
  if (!symbOpt.has_value())
    return {{QChar(), QChar()}, 0};
  if (CurrentMapper().isControl(VK, Shifters))
    return {{QChar(), QChar()}, 0};
  auto symbCombOpt = getCombinedSymbol(VK, Shifters);
  QChar symbDead = getDeadKeySymbol();
  PreviousDeadKey_.reset();
  if (symbOpt->isPrint()) {
    if (symbCombOpt.has_value())
      return {{*symbCombOpt, QChar()}, 1};
    else
      return {{symbDead, *symbOpt}, 2};
  }
  // I am not sure why this special behaviour is here
  if (VK == CVK::Enter || VK == CVK::Tab)
    return {{symbDead, *symbOpt}, 2};
  return {{QChar(), QChar()}, 0};
}

CKeyTextData CKeyTextMaker::getKeyTextDataNoDeadKey(CVKCode VK,
                                                    CKeyShifters Shifters) {
  auto symbOpt = getPlainSymbol(VK, Shifters);
  if (!symbOpt.has_value())
    return {{QChar(), QChar()}, 0};
  if (CurrentMapper().isControl(VK, Shifters))
    return {{QChar(), QChar()}, 0};
  if (symbOpt->isPrint()) {
    if (isDeadKey(VK, Shifters)) {
      PreviousDeadKey_ = {VK, Shifters};
      return {{QChar(), QChar()}, 0};
    }
    return {{*symbOpt, QChar()}, 1};
  }
  if (VK == CVK::Enter || VK == CVK::Tab)
    return {{*symbOpt, QChar()}, 1};
  return {{QChar(), QChar()}, 0};
}

CKeyTextMaker::QCharOptional
CKeyTextMaker::getPlainSymbol(CVKCode VK, CKeyShifters Shifters) const {
  return CurrentMapper().getSymbol(VK, Shifters);
}

CKeyTextMaker::QCharOptional
CKeyTextMaker::getCombinedSymbol(CVKCode VK, CKeyShifters Shifters) const {
  assert(hasDeadKeyInBuffer());
  return CurrentMapper().getCombinedSymbol(DeadKey().VK, DeadKey().Shifters, VK,
                                           Shifters);
}

QChar CKeyTextMaker::getDeadKeySymbol() const {
  assert(hasDeadKeyInBuffer());
  return *getPlainSymbol(DeadKey().VK, DeadKey().Shifters);
}

const CKeyMapper& CKeyTextMaker::CurrentMapper() const {
  return CurrentMapperIt_->second;
}

const CKeyMapper& CKeyTextMaker::Mapper(HKL Layout) {
  return Mappers_.try_emplace(Layout, Layout).first->second;
}

HKL CKeyTextMaker::CurrentLayout() const {
  return CurrentMapperIt_->first;
}

const CKeyTextMaker::CKeyData& CKeyTextMaker::DeadKey() const {
  assert(hasDeadKeyInBuffer());
  return *PreviousDeadKey_;
}

bool CKeyTextMaker::hasDeadKeyInBuffer() const {
  return PreviousDeadKey_.has_value();
}

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication
