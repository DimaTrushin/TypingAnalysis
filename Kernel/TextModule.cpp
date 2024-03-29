#include "TextModule.h"

#include "AppDebug/PerformanceLogger.h"
#include "ModifiersTextDataFiller.h"

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
  CurrentTextMode_ = Mode;
  TextModeOutput_.notify();
  if (!CurrentSession_.hasData())
    return;
  handleCurrentSession(CurrentSession_.data_());
}

void CTextModuleImpl::setCurrentETextMode(ETextMode Mode) {
  if (CurrentTextMode_.TextMode == Mode)
    return;
  CurrentTextMode_.TextMode = Mode;
  TextModeOutput_.notify();
  if (!CurrentSession_.hasData())
    return;
  handleCurrentSession(CurrentSession_.data_());
}

void CTextModuleImpl::setCurrentModifiersMode(CModifiersMode Mode) {
  if (CurrentTextMode_.TextMode == ETextMode::Raw)
    return;
  if (CurrentTextMode_.Modifiers == Mode)
    return;
  CurrentTextMode_.Modifiers = Mode;
  TextModeOutput_.notify();
  if (!CurrentSession_.hasData())
    return;
  handleCurrentSession(CurrentSession_.data_());
}

CTextModuleImpl::CSessionObserver* CTextModuleImpl::currentSessionInput() {
  return &CurrentSession_;
}

void CTextModuleImpl::subscribeToTextData(CTextDataObserver* obs) {
  assert(obs);
  TextDataOutput_.subscribe(obs);
}

void CTextModuleImpl::handleCurrentSession(const CSession& Session) {
  NSAppDebug::CTimeAnchor Anchor("handle session & notify time =");
  TreeConverter_.convert(Session, &TextDataTree_);
  CModifiersTextDataFiller Filler;
  Filler.fill(Session, TextDataTree_, &ModifierTextData_);
  TextDataOutput_.set(
      CTextData(Session, TextDataTree_, ModifierTextData_, CurrentTextMode_));
}
} // namespace NSTextModuleDetail
} // namespace NSKernel
} // namespace NSApplication
