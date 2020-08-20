#include "KeyTextMaker.h"

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

QString CKeyTextMaker::get(CVKCode VK, CKeyShifters Shifters, HKL Layout) {
  if (isLayoutChanged(Layout))
    switchLayout(Layout);
  return getSymbols(VK, Shifters);
}

bool CKeyTextMaker::isLayoutChanged(HKL Layout) const {
  return Layout != CurrentLayout();
}

void CKeyTextMaker::switchLayout(HKL Layout) {
  PreviousDeadKey_.reset();
  CurrentMapperIt_ = Mappers_.try_emplace(Layout, Layout).first;
}

QString CKeyTextMaker::getSymbols(CVKCode VK, CKeyShifters Shifters) {
  if (hasDeadKeyInBuffer())
    return getSymbolsWithDeadKey(VK, Shifters);
  return getSymbolsPlain(VK, Shifters);
}

QString CKeyTextMaker::getSymbolsWithDeadKey(CVKCode VK, CKeyShifters Shifters) {
  auto symbOpt = getPlainSymbol(VK, Shifters);
  if (!symbOpt.has_value())
    return "";
  if (CurrentMapper().isControl(VK, Shifters))
    return "";
  auto symbCombOpt = getCombinedSymbol(VK, Shifters);
  QChar symbDead = getDeadKeySymbol();
  PreviousDeadKey_.reset();
  if (symbOpt->isPrint()) {
    if (symbCombOpt.has_value())
      return *symbCombOpt;
    else
      return QString(symbDead).append(*symbOpt);

  }
  if (VK == CVK::Enter)
    return QString(symbDead).append(*symbOpt);
  return "";
}

QString CKeyTextMaker::getSymbolsPlain(CVKCode VK, CKeyShifters Shifters) {
  auto symbOpt = getPlainSymbol(VK, Shifters);
  if (!symbOpt.has_value())
    return "";
  if (CurrentMapper().isControl(VK, Shifters))
    return "";
  if (symbOpt->isPrint()) {
    if (isDeadKey(VK, Shifters)) {
      PreviousDeadKey_ = {VK, Shifters};
      return "";
    }
    return *symbOpt;
  }
  if (VK == CVK::Enter)
    return *symbOpt;
  return "";
}

CKeyTextMaker::QCharOptional CKeyTextMaker::getPlainSymbol(CVKCode VK, CKeyShifters Shifters) const {
  return CurrentMapper().getSymbol(VK, Shifters);
}

CKeyTextMaker::QCharOptional CKeyTextMaker::getCombinedSymbol(CVKCode VK, CKeyShifters Shifters) const {
  assert(hasDeadKeyInBuffer());
  return CurrentMapper().getCombinedSymbol(
           DeadKey().VK, DeadKey().Shifters, VK, Shifters);
}

QChar CKeyTextMaker::getDeadKeySymbol() const {
  assert(hasDeadKeyInBuffer());
  return *getPlainSymbol(DeadKey().VK, DeadKey().Shifters);
}

const CKeyMapper& CKeyTextMaker::CurrentMapper() const {
  return CurrentMapperIt_->second;
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

bool CKeyTextMaker::isDeadKey(CVKCode VK, CKeyShifters Shifters) const {
  return CurrentMapper().isDeadKey(VK, Shifters);
}

} // NSWindows
} // NSKeyboard
} // NSApplication
