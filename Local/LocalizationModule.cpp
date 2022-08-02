#include "LocalizationModule.h"

#include <cassert>

namespace NSApplication {
namespace NSLocal {

namespace NSLocalizationModuleDetail {
void CLocalizationModuleImpl::switchLocale(ELocale Lang) {
  switch (Lang) {
  case ELocale::Eng:
    Localizer_ = CLocalizer::make<CEngLocale>();
    break;
  case ELocale::Rus:
    Localizer_ = CLocalizer::make<CRusLocale>();
    break;
  default:
    assert(false);
    break;
  }
  notifyAll();
}

void CLocalizationModuleImpl::subscribeToSeanceViewLocalizer(
    CSeanceViewLocalizerObserver* obs) {
  assert(obs);
  SeanceViewLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::subscribeToStatisticsLocalizer(
    CStatisticsLocalizerObserver* obs) {
  assert(obs);
  StatisticsLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::subscribeToStatisticsViewLocalizer(
    CStatisticsViewLocalizerObserver* obs) {
  assert(obs);
  StatistiscViewLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::subscribeToTextModeViewLocalizer(
    CTextModeViewLocalizerObserver* obs) {
  assert(obs);
  TextModeViewLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::subscribeToSpeedPlotterLocalizer(
    CSpeedPlotterLocalizerObserver* obs) {
  assert(obs);
  SpeedPlotterLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::subscribeToKeySchemePlotterLocalizer(
    CKeySchemePlotterLocalizerObserver* obs) {
  assert(obs);
  KeySchemePlotterLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::subscribeToFileMenuLocalizer(
    CFileMenuLocalizerObserver* obs) {
  assert(obs);
  FileMenuLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::notifyAll() {
  SeanceViewLocalizerOutput_.notify();
  StatistiscViewLocalizerOutput_.notify();
  StatisticsLocalizerOutput_.notify();
  TextModeViewLocalizerOutput_.notify();
  SpeedPlotterLocalizerOutput_.notify();
  KeySchemePlotterLocalizerOutput_.notify();
  FileMenuLocalizerOutput_.notify();
}

CLocalizationModuleImpl::CSeanceViewLocalizerObservable
NSLocalizationModuleDetail::CLocalizationModuleImpl::makeSeanceViewLocalizer() {
  return CSeanceViewLocalizerObservable([this]() -> CSeanceViewGetType {
    return Localizer_.getSeanceViewLocalizer();
  });
}

CLocalizationModuleImpl::CStatisticsViewLocalizerObservable
CLocalizationModuleImpl::makeStatisticsViewLocalizer() {
  return CStatisticsViewLocalizerObservable([this]() -> CStatisticsViewGetType {
    return Localizer_.getStatisticsViewLocalizer();
  });
}

CLocalizationModuleImpl::CStatisticsLocalizerObservable
CLocalizationModuleImpl::makeStatisticsLocalizer() {
  return CStatisticsLocalizerObservable([this]() -> CStatisticsGetType {
    return Localizer_.getStatisticsLoalizer();
  });
}

CLocalizationModuleImpl::CTextModeViewLocalizerObservable
CLocalizationModuleImpl::makeTextModeViewLocalizer() {
  return CTextModeViewLocalizerObservable([this]() -> CTextModeViewGetType {
    return Localizer_.getTextModeViewLocalizer();
  });
}

CLocalizationModuleImpl::CSpeedPlotterLocalizerObservable
CLocalizationModuleImpl::makeSpeedPlotterLocalizer() {
  return CSpeedPlotterLocalizerObservable([this]() -> CSpeedPlotterGetType {
    return Localizer_.getSpeedPlotterLocalizer();
  });
}

CLocalizationModuleImpl::CKeySchemePlotterLocalizerObservable
CLocalizationModuleImpl::makeKeySchemePlotterLocalizer() {
  return CKeySchemePlotterLocalizerObservable(
      [this]() -> CKeySchemePlotterGetType {
        return Localizer_.getKeySchemePlotterLocalizer();
      });
}

CLocalizationModuleImpl::CFileMenuLocalizerObservable
CLocalizationModuleImpl::makeFileMenuLocalizer() {
  return CFileMenuLocalizerObservable([this]() -> CFileMenuGetType {
    return Localizer_.getFileMenuLocalizer();
  });
}
} // namespace NSLocalizationModuleDetail
} // namespace NSLocal
} // namespace NSApplication
