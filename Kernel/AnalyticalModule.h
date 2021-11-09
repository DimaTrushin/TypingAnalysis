#ifndef NSAPPLICATION_NSKERNEL_CANALYTICALMODULE_H
#define NSAPPLICATION_NSKERNEL_CANALYTICALMODULE_H

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "PlotData.h"
#include "TextData.h"

namespace NSApplication {
namespace NSKernel {

class CFunctionData {
  using CContainer = std::vector<double>;

public:
  void set(CContainer&& Samples);
  const CPlotData& plotData() const;

  double compute0(double arg) const;
  double compute1(double arg) const;

private:
  CContainer Samples_;
  CNormalApproximation0 Density0_{};
  CNormalApproximation1 Density1_{};
  CMaxwellBoltzmannApproximation0 DensityMB0_{};
  CMaxwellBoltzmannApproximation1 DensityMB1_{};
  CPlotData PlotData_;
};

namespace NSAnalyticalModuleDetail {
class CAnalyticalModuleImpl {
  using CContainer = std::vector<double>;

  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CPlotDataObserver = NSLibrary::CObserver<CPlotData>;
  using CPlotDataObservable = NSLibrary::CObservable<CPlotData>;
  using CPlotDataGetType = CPlotDataObserver::CGetType;

public:
  CAnalyticalModuleImpl();

  CTextDataObserver* textDataInput();
  void subscribeToSpeedData(CPlotDataObserver* obs);

private:
  void handleTextData(const CTextData& Data);

  CContainer getSpeedData(const CTextData& Data) const;
  CContainer getRawSpeedData(const CSession& Session) const;
  CContainer getFullTextSpeedData(const CTextDataTree& TextTree) const;
  CContainer getTextSpeedData(const CTextDataTree& TextTree) const;

  CFunctionData SpeedData_;
  CTextDataInput TextData_;
  CPlotDataObservable DensityOut_;
};

} // namespace NSAnalyticalModuleDetail

using CAnalyticalModule =
    NSLibrary::CModelWrapper<NSAnalyticalModuleDetail::CAnalyticalModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H
