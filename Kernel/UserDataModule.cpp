#include "UserDataModule.h"

namespace NSApplication {
namespace NSKernel {
namespace NSUserDataModuleDetail {

CUserDataModuleImpl::CUserDataModuleImpl()
    : FingerLayoutOutput_(CFingerLayout::getDefault()) {
}

void CUserDataModuleImpl::subscribeToFingerLayout(CFingerLayoutObserver* obs) {
  assert(obs);
  FingerLayoutOutput_.subscribe(obs);
}

void CUserDataModuleImpl::setFingerLayout(CFingerLayout&& FingerLayout) {
  FingerLayoutOutput_.set(std::move(FingerLayout));
}

} // namespace NSUserDataModuleDetail
} // namespace NSKernel
} // namespace NSApplication
