#ifndef NSAPPLICATION_NSKERNEL_CTEXTMODULE_H
#define NSAPPLICATION_NSKERNEL_CTEXTMODULE_H

#include "Kernel/Session.h"
#include "Kernel/TextData.h"
#include "Kernel/TextMode.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {

namespace NSTextModuleDetail {
class CTextModuleImpl {
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeObservable = NSLibrary::CObservable<CTextMode>;
  using CTextModeGetType = CTextModeObserver::CGetType;

  using CSessionObserver = NSLibrary::CObserver<CSession>;
  using CSessionGetType = CSessionObserver::CGetType;
  using CSessionInput = NSLibrary::CHotInput<CSession>;

  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataGetType = CTextDataObserver::CGetType;
  using CTextDataObservable = NSLibrary::CObservableData<CTextData>;

public:
  CTextModuleImpl();
  void subscribeToCurrentTextMode(CTextModeObserver* obs);
  void setCurrentTextMode(CTextMode);

  CSessionObserver* currentSessionInput();
  void subscribeToTextData(CTextDataObserver* obs);

private:
  void handleCurrentSession(const CSession& Seance);

  CSessionInput CurrentSession_;
  CTextMode CurrentTextMode_;
  CTextModeObservable TextModeOutput_;
  CTextDataObservable TextDataOutput_;
};

} // namespace NSTextModuleDetail

using CTextModule =
    NSLibrary::CModelWrapper<NSTextModuleDetail::CTextModuleImpl>;
} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTMODULE_H
