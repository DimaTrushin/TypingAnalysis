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

bool CModifierDatum::isAutoRepeat() const {
  return Key_.isAutoRepeat();
}

CTime CModifierDatum::getPressingTime() const {
  return Key_.getPressingTime();
}

CTime CModifierDatum::getReleasingTime() const {
  return Key_.getReleasingTime();
}

QChar CModifierDatum::getSymbol() const {
  return Key_.getLabel().LowSymbol;
}

size_t CModifierData::amountOfKeys() const {
  return Keys_.size();
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
  Keys_.push_back(Key);
}

void CModifierData::push_back(CModifierDatum&& Key) {
  Keys_.push_back(std::move(Key));
}

void CModifierData::clear() {
  Keys_.clear();
}

CModifierData::iterator CModifierData::begin() {
  return Keys_.begin();
}

CModifierData::const_iterator CModifierData::begin() const {
  return Keys_.begin();
}

CModifierData::const_iterator CModifierData::cbegin() const {
  return Keys_.cbegin();
}

CModifierData::iterator CModifierData::end() {
  return Keys_.end();
}

CModifierData::const_iterator CModifierData::end() const {
  return Keys_.end();
}

CModifierData::const_iterator CModifierData::cend() const {
  return Keys_.cend();
}

size_t CModifierData::getNumberOfEssential(ETextMode TextMode) const {
  return std::count_if(Keys_.begin(), Keys_.end(),
                       [&TextMode](const CModifierDatum& key) {
                         return key.isEssential(TextMode);
                       });
}

} // namespace NSKernel
} // namespace NSApplication
