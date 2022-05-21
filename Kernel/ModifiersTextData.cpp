#include "ModifiersTextData.h"

namespace NSApplication {
namespace NSKernel {

CModifierDatum::CModifierDatum(const CKeyEvent& Key) : Key_(Key) {
  assert(Key_.isShift() || Key_.isCtrl() || Key_.isAlt());
}

CModifierDatum::CMultiplicity
CModifierDatum::getDependencies(ETextMode mode) const {
  switch (mode) {
  case ETextMode::Full:
    return FullDependencies_;
  case ETextMode::Printed:
    return PrintedDependencies_;
  default:
    assert(false);
    return 0;
  }
}

void CModifierDatum::increaseDependencies(ETextMode mode,
                                          CMultiplicity amount) {
  switch (mode) {
  case ETextMode::Full:
    FullDependencies_ += amount;
    break;
  case ETextMode::Printed:
    PrintedDependencies_ += amount;
    break;
  default:
    assert(false);
  }
}

bool CModifierDatum::isEssential(ETextMode mode) const {
  switch (mode) {
  case ETextMode::Full:
    return FullDependencies_ > 0;
  case ETextMode::Printed:
    return PrintedDependencies_ > 0;
  default:
    assert(false);
    return false;
  }
}

size_t CModifierData::size(ETextMode TextMode,
                           EModifierMode ModifierMode) const {
  switch (ModifierMode) {
  case EModifierMode::Non:
    return 0;
  case EModifierMode::All:
    return Keys_.size();
  case EModifierMode::Essential:
    return getNumberOfEssential(TextMode);
  default:
    assert(false);
    return 0;
  }
}

bool CModifierData::empty(ETextMode TextMode,
                          EModifierMode ModifierMode) const {
  return size(TextMode, ModifierMode) > 0;
}

void CModifierData::push_back(const CModifierDatum& Key) {
  if (Key.isEssential(ETextMode::Full))
    ++NumberOfFullEssential_;
  if (Key.isEssential(ETextMode::Printed))
    ++NumberOfPrintedEssential_;
  Keys_.push_back(Key);
}

void CModifierData::push_back(CModifierDatum&& Key) {
  if (Key.isEssential(ETextMode::Full))
    ++NumberOfFullEssential_;
  if (Key.isEssential(ETextMode::Printed))
    ++NumberOfPrintedEssential_;
  Keys_.push_back(std::move(Key));
}

size_t CModifierData::getNumberOfEssential(ETextMode TextMode) const {
  switch (TextMode) {
  case ETextMode::Full:
    return NumberOfFullEssential_;
  case ETextMode::Printed:
    return NumberOfPrintedEssential_;
  default:
    assert(false);
    return 0;
  }
}

} // namespace NSKernel
} // namespace NSApplication
