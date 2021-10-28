#include "TextModeController.h"

namespace NSApplication {
namespace NSInterface {

NSTextModeControllerDetail::CTextModeControllerImpl::CTextModeControllerImpl(
    CTextModuleImpl* TextModule)
    : TextModule_(TextModule),
      TextModeInput_([this](const CTextMode& Mode) { handleTextMode(Mode); }) {
  assert(TextModule_);
}

NSTextModeControllerDetail::CTextModeControllerImpl::CTextModeObserver*
NSTextModeControllerDetail::CTextModeControllerImpl::textModeInput() {
  return &TextModeInput_;
}

void NSTextModeControllerDetail::CTextModeControllerImpl::handleTextMode(
    const CTextMode& Mode) {
  if (Mode.isWellDefined())
    TextModule_->setCurrentTextMode(Mode);
}

CTextModeController::CTextModeController(CTextModuleImpl* TextModule)
    : Impl_(std::make_unique<CTextModeControllerImpl>(TextModule)) {
}

CTextModeController::CTextModeControllerImpl*
CTextModeController::operator->() const {
  return Impl_.get();
}

} // namespace NSInterface
} // namespace NSApplication
