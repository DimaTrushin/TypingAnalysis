#ifndef NSAPPLICATION_NSKERNEL_CUSERDATAMODULE_H
#define NSAPPLICATION_NSKERNEL_CUSERDATAMODULE_H

#include "Kernel/FingerLayout.h"
#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSKernel {

namespace NSUserDataModuleDetail {

class CUserDataModuleImpl {
  using CFingerLayoutObserver = NSLibrary::CObserver<CFingerLayout>;
  using CFingerLayoutObservable = NSLibrary::CObservableData<CFingerLayout>;

public:
  CUserDataModuleImpl();

  void subscribeToFingerLayout(CFingerLayoutObserver* obs);
  void setFingerLayout(CFingerLayout&& FingerLayout);

private:
  CFingerLayoutObservable FingerLayoutOutput_;
};

} // namespace NSUserDataModuleDetail

using CUserDataModule =
    NSLibrary::CModelWrapper<NSUserDataModuleDetail::CUserDataModuleImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CUSERDATA_H
