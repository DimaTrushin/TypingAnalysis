#ifndef NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H
#define NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H

#include "Library/StlExtension/MvcWrappers.h"

#include <vector>

namespace NSApplication {
namespace NSKernel {

class CPlotData {
  using Real = double;
  using Container = std::vector<Real>;

public:
  using CIndex = int64_t;

  CPlotData();

  CIndex gridSize() const;

  const Real* dataX() const;
  const Real* dataY0() const;
  const Real* dataY1() const;

private:
  static constexpr const CIndex kDefaultGridSize = 2500;
  static constexpr const Real kMaximum = 2500.;
  static constexpr const Real kMinimum = 1.;

  void fillXByDefault();

  bool isCorrect_() const;

  Container X_;
  Container Y0_;
  Container Y1_;
  Real Maximum_ = kMaximum;
  Real Minimum_ = kMinimum;
};

class CFunctionData {
public:
private:
  // samples
  // function
  CPlotData PlotData_;
};

namespace NSAnalitycalModuleDetail {
class CAnalitycalModuleImpl {
public:
private:
  CFunctionData SpeedData_;
};

} // namespace NSAnalitycalModuleDetail

using CAnalitycalModule =
    NSLibrary::CModelWrapper<NSAnalitycalModuleDetail::CAnalitycalModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H
