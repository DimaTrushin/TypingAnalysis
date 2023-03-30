#include "KeySchemeModule.h"

namespace NSApplication {
namespace NSKernel {

namespace NSKeySchemeModuleDetail {

CKeySchemeModuleImpl::CKeySchemeModuleImpl()
    : TextDataInput_(
          [this](const CTextData& TextData) { handleTextData(TextData); }),
      FingerLayoutInput_([this](const CFingerLayout& Layout) {
        handleFingerLayoutChange(Layout);
      }) {
}

CKeySchemeModuleImpl::CFingerLayoutObserver*
CKeySchemeModuleImpl::fingerLayoutInput() {
  return &FingerLayoutInput_;
}

CKeySchemeModuleImpl::CTextDataObserver* CKeySchemeModuleImpl::textDataInput() {
  return &TextDataInput_;
}

void CKeySchemeModuleImpl::subscribeToKeyScheme(CKeySchemeObserver* obs) {
  assert(obs);
  KeySchemeOutput_.subscribe(obs);
}

void CKeySchemeModuleImpl::handleFingerLayoutChange(
    const CFingerLayout& FingerLayout) {
  if (!TextDataInput_.hasData())
    return;
  makeKeyScheme(TextDataInput_.data(), FingerLayout);
}

void CKeySchemeModuleImpl::handleTextData(const CTextData& TextData) {
  if (!FingerLayoutInput_.hasData())
    return;
  makeKeyScheme(TextData, FingerLayoutInput_.data());
}

void CKeySchemeModuleImpl::makeKeyScheme(const CTextData& TextData,
                                         const CFingerLayout& FingerLayout) {
  KeySchemeOutput_.set(KeySchemeMaker_.make(TextData, FingerLayout));
}

} // namespace NSKeySchemeModuleDetail
} // namespace NSKernel
} // namespace NSApplication
