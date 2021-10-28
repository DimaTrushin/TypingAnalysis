#include "TextModule.h"

namespace NSApplication {
namespace NSKernel {
namespace NSTextModuleDetail {

CTextModuleImpl::CTextModuleImpl()
    : TextModeOutput_(
          [this]() -> CTextModeGetType { return CurrentTextMode_; }) {
}

void CTextModuleImpl::subscribeToCurrentTextMode(CTextModeObserver* obs) {
  assert(obs);
  TextModeOutput_.subscribe(obs);
}

void CTextModuleImpl::setCurrentTextMode(CTextMode Mode) {
  if (CurrentTextMode_ == Mode)
    return;
  CurrentTextMode_ = Mode;
  TextModeOutput_.notify();
}
} // namespace NSTextModuleDetail

CTextModule::CTextModule() : Impl_(std::make_unique<CTextModuleImpl>()) {
}

CTextModule::CTextModuleImpl* CTextModule::operator->() const {
  return Impl_.get();
}

CTextModule::CTextModuleImpl* CTextModule::model() const {
  return Impl_.get();
}

} // namespace NSKernel
} // namespace NSApplication
