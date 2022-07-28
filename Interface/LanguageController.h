#ifndef NSAPPLICATION_NSINTERFACE_CLANGUAGECONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CLANGUAGECONTROLLER_H

#include "Library/Observer2/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/LocaleID.h"
#include "Local/LocalizationModule.h"

namespace NSApplication {
namespace NSInterface {

namespace NSLanguageControllerDetail {

class CLanguageControllerImpl {
  using ELocale = NSLocal::ELocale;
  using CLocaleObserver = NSLibrary::CObserver<ELocale>;
  using CLocaleInput = NSLibrary::CColdInput<ELocale>;

  using CLocalizationModuleImpl = NSLocal::CLocalizationModule::CImplementation;

public:
  CLanguageControllerImpl(CLocalizationModuleImpl* LocalizationModule);
  CLocaleObserver* localeInput();

private:
  void setLanguage(ELocale Language);

  CLocalizationModuleImpl* LocalizationModule_;
  CLocaleInput LocaleInput_;
};

} // namespace NSLanguageControllerDetail

using CLanguageController = NSLibrary::CControllerWrapper<
    NSLanguageControllerDetail::CLanguageControllerImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CLANGUAGECONTROLLER_H
