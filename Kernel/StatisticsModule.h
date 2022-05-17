#ifndef NSAPPLICATION_NSKERNEL_CSTATISTICSMODULE_H
#define NSAPPLICATION_NSKERNEL_CSTATISTICSMODULE_H

#include "AnalyticData.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/Localizer.h"
#include "StatisticsDescription.h"

#include <deque>

namespace NSApplication {
namespace NSKernel {

namespace NSStatisticsModuleDetail {

class CStatisticsModuleImpl {
  using CAnalyticData = NSKernel::CAnalyticData;
  using CAnalyticDataObserver = NSLibrary::CObserver<CAnalyticData>;
  using CAnalyticDataInput = NSLibrary::CHotInput<CAnalyticData>;

  using CStatisticsDescriptionObserver =
      NSLibrary::CObserver<CStatisticsDescription>;
  using CStatisticsDescriptionGetType =
      CStatisticsDescriptionObserver::CGetType;
  using CStatisticsDescriptionObservable =
      NSLibrary::CObservableData<CStatisticsDescription>;

  using CLocalizer = NSLocal::CStatisticsLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

public:
  CStatisticsModuleImpl();
  CAnalyticDataObserver* analyticDataInput();
  CLocalizerInput* localizerInput();
  void subscribeToStatisticsDescription(CStatisticsDescriptionObserver* obs);

private:
  void setLocale(const CLocalizer& Localizer);

  void handleAnalyticData(const CAnalyticData& Data);

  QString fullTextLength() const;
  QString printedTextLength() const;
  QString deletedSymbols() const;
  QString mistakePlaces() const;
  QString mistakes() const;
  QString mistakesPercent() const;
  QString fullTextDuration() const;
  QString printedTextDuration() const;
  QString fullTextSpeed() const;
  QString printedTextSpeed() const;
  QString maxLikelihoodSpeed() const;

  CLocalizerInput LocalizerInput_;
  CAnalyticDataInput AnalyticDataInput_;
  CStatisticsDescriptionObservable StatisticsDescriptionOutput_;
};

} // namespace NSStatisticsModuleDetail

using CStatisticsModule =
    NSLibrary::CModelWrapper<NSStatisticsModuleDetail::CStatisticsModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSTATISTICSMODULE_H
