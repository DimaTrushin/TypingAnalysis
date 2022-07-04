#include "ModifiersModeController.h"

namespace NSApplication {
namespace NSInterface {

namespace NSModifiersModeControllerDetail {

CModifiersModeControllerImpl::CModifiersModeControllerImpl(
    CTextModuleImpl* TextModule)
    : TextModule_(TextModule),
      TextModeInput_(
          [this](const CModifiersMode& Mode) { handleTextMode(Mode); }) {
}

CModifiersModeControllerImpl::CTextModeObserver*
CModifiersModeControllerImpl::textModeInput() {
  return &TextModeInput_;
}

void CModifiersModeControllerImpl::handleTextMode(const CModifiersMode& Mode) {
  TextModule_->setCurrentModifiersMode(Mode);
}

} // namespace NSModifiersModeControllerDetail

} // namespace NSInterface
} // namespace NSApplication
