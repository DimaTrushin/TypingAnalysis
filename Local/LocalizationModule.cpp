#include "LocalizationModule.h"

#include <QDebug>
#include <cassert>

namespace NSApplication {
namespace NSLocal {

namespace NSLocalizationModuleDetail {
void CLocalizationModuleImpl::subcribeToSeanceViewLocalizer(
    CSeanceViewLocalizerObserver* obs) {
  assert(obs);
  SeanceViewLocalizerOutput_.subscribe(obs);
}

void CLocalizationModuleImpl::subscribeToTextModeViewLocalizer(
    CTextModeViewLocalizerObserver* obs) {
  assert(obs);
  TextModeViewLocalizerOutput_.subscribe(obs);
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
} // namespace NSLocalizationModuleDetail
} // namespace NSLocal
} // namespace NSApplication
