#ifndef NSAPPLICATION_NSLOCAL_CLOCALIZATIONMODULE_H
#define NSAPPLICATION_NSLOCAL_CLOCALIZATIONMODULE_H

#include "Local/Localizer.h"
#include "Local/RusLocale.h"

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSLocal {

namespace NSLocalizationModuleDetail {

class CLocalizationModuleImpl {
  using CSeanceViewLocalizerObserver =
      NSLibrary::CObserver<CSeanceViewLocalizer>;
  using CSeanceViewLocalizerObservable =
      NSLibrary::CObservable<CSeanceViewLocalizer>;
  using CSeanceViewGetType = CSeanceViewLocalizerObserver::CGetType;

  using CStatisticsViewLocalizerObserver =
      NSLibrary::CObserver<CStatisticsViewLocalizer>;
  using CStatisticsViewLocalizerObservable =
      NSLibrary::CObservable<CStatisticsViewLocalizer>;
  using CStatisticsViewGetType = CStatisticsViewLocalizerObserver::CGetType;

  using CTextModeViewLocalizerObserver =
      NSLibrary::CObserver<CTextModeViewLocalizer>;
  using CTextModeViewLocalizerObservable =
      NSLibrary::CObservable<CTextModeViewLocalizer>;
  using CTextModeViewGetType = CTextModeViewLocalizerObserver::CGetType;

  using CSpeedPlotterLocalizerObserver =
      NSLibrary::CObserver<CSpeedPlotterLocalizer>;
  using CSpeedPlotterLocalizerObservable =
      NSLibrary::CObservable<CSpeedPlotterLocalizer>;
  using CSpeedPlotterGetType = CSpeedPlotterLocalizerObserver::CGetType;

  using CKeySchemePlotterLocalizerObserver =
      NSLibrary::CObserver<CKeySchemePlotterLocalizer>;
  using CKeySchemePlotterLocalizerObservable =
      NSLibrary::CObservable<CKeySchemePlotterLocalizer>;
  using CKeySchemePlotterGetType = CKeySchemePlotterLocalizerObserver::CGetType;

public:
  CLocalizationModuleImpl() = default;

  void subscribeToSeanceViewLocalizer(CSeanceViewLocalizerObserver* obs);
  void
  subscribeToStatisticsViewLocalizer(CStatisticsViewLocalizerObserver* obs);
  void subscribeToTextModeViewLocalizer(CTextModeViewLocalizerObserver* obs);
  void subscribeToSpeedPlotterLocalizer(CSpeedPlotterLocalizerObserver* obs);
  void
  subscribeToKeySchemePlotterLocalizer(CKeySchemePlotterLocalizerObserver* obs);

private:
  CSeanceViewLocalizerObservable makeSeanceViewLocalizer();
  CStatisticsViewLocalizerObservable makeStatisticsViewLocalizer();
  CTextModeViewLocalizerObservable makeTextModeViewLocalizer();
  CSpeedPlotterLocalizerObservable makeSpeedPlotterLocalizer();
  CKeySchemePlotterLocalizerObservable makeKeySchemePlotterLocalizer();

  CLocalizer Localizer_ = CLocalizer::make<CRusLocale>();

  CSeanceViewLocalizerObservable SeanceViewLocalizerOutput_ =
      makeSeanceViewLocalizer();
  CStatisticsViewLocalizerObservable StatistiscViewLocalizerOutput_ =
      makeStatisticsViewLocalizer();
  CTextModeViewLocalizerObservable TextModeViewLocalizerOutput_ =
      makeTextModeViewLocalizer();
  CSpeedPlotterLocalizerObservable SpeedPlotterLocalizerOutput_ =
      makeSpeedPlotterLocalizer();
  CKeySchemePlotterLocalizerObservable KeySchemePlotterLocalizerOutput_ =
      makeKeySchemePlotterLocalizer();
};

} // namespace NSLocalizationModuleDetail

using CLocalizationModule = NSLibrary::CBasicWrapper<
    NSLocalizationModuleDetail::CLocalizationModuleImpl>;

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CLOCALIZATIONMODULE_H
