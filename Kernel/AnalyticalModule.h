#ifndef NSAPPLICATION_NSKERNEL_CANALYTICALMODULE_H
#define NSAPPLICATION_NSKERNEL_CANALYTICALMODULE_H

#include "AnalyticData.h"
#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "PlotData.h"
#include "TextData.h"
#include "TextModeCacher.h"

namespace NSApplication {
namespace NSKernel {

class CFunctionData {
  using CContainer = std::vector<double>;

public:
  CFunctionData(CContainer&& Samples);

  void set(CContainer&& Samples);
  const CPlotData& plotData() const;

private:
  CContainer Samples_;
  CPlotData PlotData_;
};

namespace NSAnalyticalModuleDetail {
class CAnalyticalModuleImpl {
  using CContainer = std::vector<double>;

  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CPlotDataCRef = std::reference_wrapper<const CPlotData>;

  using CPlotDataObserver = NSLibrary::CObserver<CPlotDataCRef>;
  using CPlotDataObservable = NSLibrary::CObservableData<CPlotDataCRef>;

  using CFunctionDataPtr = std::unique_ptr<CFunctionData>;
  using CCacher = CTextModeCacher<CFunctionDataPtr>;

  using CAnalyticDataObserver = NSLibrary::CObserver<CAnalyticData>;
  using CAnalyticDataObservable = NSLibrary::CObservableData<CAnalyticData>;

public:
  CAnalyticalModuleImpl();

  CTextDataObserver* textDataInput();
  void subscribeToSpeedData(CPlotDataObserver* obs);
  void subscribeToAnalyticData(CAnalyticDataObserver* obs);

private:
  void handleTextData(const CTextData& Data);

  CContainer getSpeedData(const CTextData& Data) const;
  template<class TSequencer>
  CContainer getSpeedDataS(TSequencer Sequencer) const;

  CFunctionDataPtr SpeedData_;
  CTime TimeLimit_ = CTime::MilliSeconds(50);
  CCacher SpeedDataCacher_;
  CTextDataInput TextData_;
  CPlotDataObservable DensityOut_;
  CAnalyticDataObservable AnalyticDataOut_;
};

} // namespace NSAnalyticalModuleDetail

using CAnalyticalModule =
    NSLibrary::CModelWrapper<NSAnalyticalModuleDetail::CAnalyticalModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H
