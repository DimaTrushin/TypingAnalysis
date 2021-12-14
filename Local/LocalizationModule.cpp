#include "LocalizationModule.h"

#include <QDebug>
#include <cassert>

namespace NSApplication {
namespace NSLocal {

namespace NSLocalizationModuleDetail {
void CLocalizationModuleImpl::subscribeToSeanceViewLocalizer(
    CSeanceViewLocalizerObserver* obs) {
  assert(obs);
  SeanceViewLocalizerOutput_.subscribe(obs);
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

CLocalizationModuleImpl::CSeanceViewLocalizerObservable
NSLocalizationModuleDetail::CLocalizationModuleImpl::makeSeanceViewLocalizer() {
  return CSeanceViewLocalizerObservable([this]() -> CSeanceViewGetType {
    return Localizer_.getSeanceViewLocalizer();
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
} // namespace NSLocalizationModuleDetail
} // namespace NSLocal
} // namespace NSApplication
