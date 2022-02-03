#ifndef NSAPPLICATION_NSKERNEL_CANALYTICALMODULE_H
#define NSAPPLICATION_NSKERNEL_CANALYTICALMODULE_H

#include "Library/Observer/Observer.h"
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

  using CPlotDataObserver = NSLibrary::CObserver<CPlotData>;
  using CPlotDataObservable = NSLibrary::CObservable<CPlotData>;
  using CPlotDataGetType = CPlotDataObserver::CGetType;

  using CFunctionDataPtr = std::unique_ptr<CFunctionData>;
  using CCacher = CTextModeCacher<CFunctionDataPtr>;

public:
  CAnalyticalModuleImpl();

  CTextDataObserver* textDataInput();
  void subscribeToSpeedData(CPlotDataObserver* obs);

private:
  void handleTextData(const CTextData& Data);

  CContainer getSpeedData(const CTextData& Data) const;
  template<class TText>
  CContainer getSpeedData(const TText& TextView) const;

  CFunctionDataPtr SpeedData_;
  CTime TimeLimit_ = CTime::MilliSeconds(50);
  CCacher SpeedDataCacher_;
  CTextDataInput TextData_;
  CPlotDataObservable DensityOut_;
};

} // namespace NSAnalyticalModuleDetail

using CAnalyticalModule =
    NSLibrary::CModelWrapper<NSAnalyticalModuleDetail::CAnalyticalModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CANALITYCALMODULE_H
