#ifndef NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATA_H
#define NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATA_H

#include "KeyEvent.h"
#include "TextMode.h"

#include <vector>

namespace NSApplication {
namespace NSKernel {

class CModifierDatum {
public:
  using CMultiplicity = unsigned char;

  explicit CModifierDatum(const CKeyEvent& Key);

  CMultiplicity getDependencies(ETextMode mode) const;
  void increaseDependencies(ETextMode mode, CMultiplicity amount);
  bool isEssential(ETextMode mode) const;

  CTime getPressingTime() const;
  CTime getReleasingTime() const;

private:
  CKeyEvent Key_;
  CMultiplicity PrintedDependencies_ = 0;
  CMultiplicity FullDependencies_ = 0;
};

class CModifierData {
  using CContainer = std::vector<CModifierDatum>;
  using CMultiplicity = CModifierDatum::CMultiplicity;

public:
  using iterator = CContainer::iterator;
  using const_iterator = CContainer::const_iterator;

  size_t amountOfKeys() const;
  size_t size(ETextMode TextMode, EModifierMode ModifierMode) const;
  bool empty(ETextMode TextMode, EModifierMode ModifierMode) const;

  void push_back(const CModifierDatum& Key);
  void push_back(CModifierDatum&& Key);
  void clear();

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

private:
  size_t getNumberOfEssential(ETextMode TextMode) const;

  CContainer Keys_;
};

struct CModifiersTextData {
  CModifierData Shifts;
  CModifierData Ctrls;
  CModifierData Alts;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATA_H
