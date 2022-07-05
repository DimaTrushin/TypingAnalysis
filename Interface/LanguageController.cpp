#include "LanguageController.h"

namespace NSApplication {
namespace NSInterface {

namespace NSLanguageControllerDetail {
CLanguageControllerImpl::CLanguageControllerImpl(
    CLocalizationModuleImpl* LocalizationModule)
    : LocalizationModule_(LocalizationModule),
      LocaleInput_([this](ELocale Language) { setLanguage(Language); }) {
}

CLanguageControllerImpl::CLocaleObserver*
CLanguageControllerImpl::localeInput() {
  return &LocaleInput_;
}

void CLanguageControllerImpl::setLanguage(ELocale Language) {
  LocalizationModule_->switchLocale(Language);
}
} // namespace NSLanguageControllerDetail
} // namespace NSInterface
} // namespace NSApplication
