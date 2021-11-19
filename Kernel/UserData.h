#ifndef NSAPPLICATION_NSKERNEL_CUSERDATA_H
#define NSAPPLICATION_NSKERNEL_CUSERDATA_H

#include "Kernel/FingerLayout.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSKernel {

namespace NSUserDataDetail {

class CUserDataImpl {
  using CFingerLayoutObserver = NSLibrary::CObserver<CFingerLayout>;
  using CFingerLayoutObservable = NSLibrary::CObservableData<CFingerLayout>;

public:
  CUserDataImpl();

  void subscribeToFingerLayout(CFingerLayoutObserver* obs);
  void setFingerLayout(CFingerLayout&& FingerLayout);

private:
  CFingerLayoutObservable FingerLayoutOutput_;
};

} // namespace NSUserDataDetail

using CUserData = NSLibrary::CModelWrapper<NSUserDataDetail::CUserDataImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CUSERDATA_H
