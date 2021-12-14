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

  using CTextModeViewLocalizerObserver =
      NSLibrary::CObserver<CTextModeViewLocalizer>;
  using CTextModeViewLocalizerObservable =
      NSLibrary::CObservable<CTextModeViewLocalizer>;
  using CTextModeViewGetType = CTextModeViewLocalizerObserver::CGetType;

public:
  CLocalizationModuleImpl() = default;

  void subcribeToSeanceViewLocalizer(CSeanceViewLocalizerObserver* obs);
  void subscribeToTextModeViewLocalizer(CTextModeViewLocalizerObserver* obs);

private:
  CSeanceViewLocalizerObservable makeSeanceViewLocalizer();
  CTextModeViewLocalizerObservable makeTextModeViewLocalizer();

  CLocalizer Localizer_ = CLocalizer::make<CRusLocale>();
  CSeanceViewLocalizerObservable SeanceViewLocalizerOutput_ =
      makeSeanceViewLocalizer();
  CTextModeViewLocalizerObservable TextModeViewLocalizerOutput_ =
      makeTextModeViewLocalizer();
};

} // namespace NSLocalizationModuleDetail

using CLocalizationModule = NSLibrary::CBasicWrapper<
    NSLocalizationModuleDetail::CLocalizationModuleImpl>;

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CLOCALIZATIONMODULE_H
