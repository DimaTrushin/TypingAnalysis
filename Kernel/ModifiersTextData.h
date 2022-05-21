#ifndef NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATA_H
#define NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATA_H

#include "KeyEvent.h"
#include "TextMode.h"

#include <vector>

namespace NSApplication {
namespace NSKernel {

class CModifierDatum {
  using CMultiplicity = unsigned char;

public:
  explicit CModifierDatum(const CKeyEvent& Key);

  CMultiplicity getDependencies(ETextMode mode) const;
  void increaseDependencies(ETextMode mode, CMultiplicity amount);
  bool isEssential(ETextMode mode) const;

private:
  CKeyEvent Key_;
  CMultiplicity PrintedDependencies_ = 0;
  CMultiplicity FullDependencies_ = 0;
};

class CModifierData {
  using CContainer = std::vector<CModifierDatum>;

public:
  size_t size(ETextMode TextMode, EModifierMode ModifierMode) const;
  bool empty(ETextMode TextMode, EModifierMode ModifierMode) const;

  void push_back(const CModifierDatum& Key);
  void push_back(CModifierDatum&& Key);

private:
  size_t getNumberOfEssential(ETextMode TextMode) const;

  CContainer Keys_;
  size_t NumberOfPrintedEssential_ = 0;
  size_t NumberOfFullEssential_ = 0;
};

struct CModifiersTextData {
  CModifierData Shifts;
  CModifierData Ctrls;
  CModifierData Alts;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATA_H
