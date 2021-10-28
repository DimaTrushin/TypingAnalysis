#include "TextModule.h"
#include <QDebug>

namespace NSApplication {
namespace NSKernel {
namespace NSTextModuleDetail {

CTextModuleImpl::CTextModuleImpl()
    : CurrentSession_(
          [this](const CSession& Session) { handleCurrentSession(Session); }),
      TextModeOutput_(
          [this]() -> CTextModeGetType { return CurrentTextMode_; }) {
}

void CTextModuleImpl::subscribeToCurrentTextMode(CTextModeObserver* obs) {
  assert(obs);
  TextModeOutput_.subscribe(obs);
}

void CTextModuleImpl::setCurrentTextMode(CTextMode Mode) {
  if (CurrentTextMode_ == Mode)
    return;
  assert(Mode.isWellDefined());
  CurrentTextMode_ = Mode;
  TextModeOutput_.notify();
  if (!CurrentSession_.hasValue())
    return;
  handleCurrentSession(*CurrentSession_.data());
}

CTextModuleImpl::CSessionObserver* CTextModuleImpl::currentSessionInput() {
  return &CurrentSession_;
}

void CTextModuleImpl::subscribeToTextData(CTextDataObserver* obs) {
  assert(obs);
  TextDataOutput_.subscribe(obs);
}

void CTextModuleImpl::handleCurrentSession(const CSession& Session) {
  qDebug() << "CTextModule::handleCurrentSession";
  // TO DO
  // Do some work to construct CSessionData
  // This is a preliminary version
  TextDataOutput_.set(CTextData{std::cref(Session)});
}
} // namespace NSTextModuleDetail
} // namespace NSKernel
} // namespace NSApplication
