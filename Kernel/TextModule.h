#ifndef NSAPPLICATION_NSKERNEL_CTEXTMODULE_H
#define NSAPPLICATION_NSKERNEL_CTEXTMODULE_H

#include "Kernel/TextMode.h"
#include "Library/Observer/Observer.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {

namespace NSTextModuleDetail {
class CTextModuleImpl {
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeObservable = NSLibrary::CObservable<CTextMode>;
  using CTextModeGetType = CTextModeObserver::CGetType;

public:
  CTextModuleImpl();
  void subscribeToCurrentTextMode(CTextModeObserver* obs);
  void setCurrentTextMode(CTextMode);

private:
  CTextMode CurrentTextMode_;
  CTextModeObservable TextModeOutput_;
};

} // namespace NSTextModuleDetail

class CTextModule {
public:
  using CTextModuleImpl = NSTextModuleDetail::CTextModuleImpl;

  CTextModule();

  CTextModuleImpl* operator->() const;
  CTextModuleImpl* model() const;

private:
  std::unique_ptr<CTextModuleImpl> Impl_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTMODULE_H
