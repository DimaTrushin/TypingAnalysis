#ifndef NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H
#define NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "MathFunction.h"
#include "TextData.h"

#include <vector>

namespace NSApplication {
namespace NSKernel {

class CPlotData {
  using CContainer = std::vector<double>;

public:
  using CIndex = int64_t;

  CPlotData();
  CPlotData(CIndex GridSize);

  CIndex gridSize() const;

  const double* dataX() const;
  const double* dataY0() const;
  const double* dataY1() const;

  void fillY0(const CContainer& Samples, const CDensity0& F);
  void fillY1(const CContainer& Samples, const CDensity1& F);

private:
  static constexpr const CIndex kDefaultGridSize = 2500;
  static constexpr const double kMaximum = 2500.;
  static constexpr const double kMinimum = 1.;

  void fillX();

  bool isCorrect_() const;

  CContainer X_;
  CContainer Y0_;
  CContainer Y1_;
  double Maximum_ = kMaximum;
  double Minimum_ = kMinimum;
};

class CFunctionData {
  using CContainer = std::vector<double>;

public:
  void set(CContainer&& Samples);
  const CPlotData& plotData() const;

private:
  CContainer Samples_;
  CDensity0 Density0_{};
  CDensity1 Density1_{};
  CPlotData PlotData_;
};

namespace NSAnalitycalModuleDetail {
class CAnalitycalModuleImpl {
  using CContainer = std::vector<double>;

  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CPlotDataObserver = NSLibrary::CObserver<CPlotData>;
  using CPlotDataObservable = NSLibrary::CObservable<CPlotData>;
  using CPlotDataGetType = CPlotDataObserver::CGetType;

public:
  CAnalitycalModuleImpl();

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

} // namespace NSAnalitycalModuleDetail

using CAnalitycalModule =
    NSLibrary::CModelWrapper<NSAnalitycalModuleDetail::CAnalitycalModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H
