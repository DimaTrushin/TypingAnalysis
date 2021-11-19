#ifndef NSAPPLICATION_NSKERNEL_CKEYSCHEMEMODULE_H
#define NSAPPLICATION_NSKERNEL_CKEYSCHEMEMODULE_H

#include "Kernel/FingerLayout.h"
#include "Kernel/TextData.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSKernel {

namespace NSKeySchemeModuleDetail {

class CKeySchemeModuleImpl {
  using CFingerLayoutObserver = NSLibrary::CObserver<CFingerLayout>;
  using CFingerLayoutInput = NSLibrary::CHotInput<CFingerLayout>;

  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

public:
  CKeySchemeModuleImpl();
  CFingerLayoutObserver* fingerLayoutInput();
  CTextDataObserver* textDataInput();

private:
  void handleFingerLayoutChange(const CFingerLayout& FingerLayout);
  void handleTextData(const CTextData& TextData);
  void makeKeyScheme(const CTextData& TextData,
                     const CFingerLayout& FingerLayout);

  CTextDataInput TextDataInput_;
  CFingerLayoutInput FingerLayoutInput_;
};

} // namespace NSKeySchemeModuleDetail

using CKeySchemeModule =
    NSLibrary::CModelWrapper<NSKeySchemeModuleDetail::CKeySchemeModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYSCHEMEMAKER_H
