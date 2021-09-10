#include "TextModule.h"

namespace NSApplication {
namespace NSKernel {

namespace NSTextModuleDetail {

CTextModuleImpl::CTextModuleImpl()
    : SessionInput_([this](CSessionGetType Session) { setSession(Session); }),
      TextModeInput_([this](CTextMode Mode) { setMode(Mode); }),
      TextOutput_([this]() -> CQStringGetType { return Text_; }) {
}

void CTextModuleImpl::subscribeToText(CQStringObserver* observer) {
  TextOutput_.subscribe(observer);
}

CTextModuleImpl::CSessionObserver* CTextModuleImpl::sessionInput() {
  return &SessionInput_;
}

CTextModuleImpl::CTextModeObserver* CTextModuleImpl::textModeInput() {
  return &TextModeInput_;
}

void CTextModuleImpl::setSession(CSessionGetType Session) {
  Session_ = Session;
  if (TextModeInput_.isActive()) {
    processSession();
  }
}

void CTextModuleImpl::setMode(CTextMode Mode) {
  if (Mode != Mode_) {
    Mode_ = Mode;
    if (Session_.has_value()) {
      processSession();
    }
  }
}

void CTextModuleImpl::processSession() {
  resetResources();
  if (Session_.has_value()) {
    makeText();
  }
  TextOutput_.notify();
}

void CTextModuleImpl::makeText() {
  if (Mode_ == CTextMode::Raw) {
    Text_ = *scanSession();
  }
  if (Mode_ == CTextMode::Printed) {
    Text_ = *(new QString(""));
  }
  if (Mode_ == CTextMode::Full) {
    Text_ = *(new QString(""));
  }
}

QString* CTextModuleImpl::scanSession() {
  return SessionScanner_.run(Session_->get(), new QString());
}

void CTextModuleImpl::resetResources() {
  resetText();
}

void CTextModuleImpl::resetText() {
  Text_.reset();
}

} // namespace NSTextModuleDetail

namespace NSTextModule {

CTextModule::CTextModule() : Impl_(std::make_unique<CTextModuleImpl>()) {
}

CTextModule::CTextModuleImpl* CTextModule::operator->() {
  return Impl_.get();
}

} // namespace NSTextModule

} // namespace NSKernel
} // namespace NSApplication
