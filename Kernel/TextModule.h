#ifndef NSAPPLICATION_NSKERNEL_CTEXTMODULE_H
#define NSAPPLICATION_NSKERNEL_CTEXTMODULE_H

#include "Kernel/Session.h"
#include "Kernel/SessionToTreeConverter.h"
#include "Kernel/TextData.h"
#include "Kernel/TextDataTree.h"
#include "Kernel/TextMode.h"
#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "ModifiersTextData.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {

namespace NSTextModuleDetail {
class CTextModuleImpl {
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeObservable = NSLibrary::CObservable<CTextMode>;
  using CTextModeGetType = CTextModeObservable::CGetType;

  using CSessionObserver = NSLibrary::CObserver<CSession>;
  using CSessionInput = NSLibrary::CHotInput<CSession>;

  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataObservable = NSLibrary::CObservableData<CTextData>;

public:
  CTextModuleImpl();
  void subscribeToCurrentTextMode(CTextModeObserver* obs);
  void setCurrentTextMode(CTextMode);
  void setCurrentETextMode(ETextMode);
  void setCurrentModifiersMode(CModifiersMode);

  CSessionObserver* currentSessionInput();
  void subscribeToTextData(CTextDataObserver* obs);

private:
  void handleCurrentSession(const CSession& Seance);

  CSessionInput CurrentSession_;
  CTextMode CurrentTextMode_;
  CTextDataTree TextDataTree_;
  CModifiersTextData ModifierTextData_;
  CSessionToTreeConverter TreeConverter_;
  CTextModeObservable TextModeOutput_;
  CTextDataObservable TextDataOutput_;
};

} // namespace NSTextModuleDetail

using CTextModule =
    NSLibrary::CModelWrapper<NSTextModuleDetail::CTextModuleImpl>;
} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTMODULE_H
