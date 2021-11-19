#include "UserData.h"

namespace NSApplication {
namespace NSKernel {
namespace NSUserDataDetail {

CUserDataImpl::CUserDataImpl()
    : FingerLayoutOutput_(CFingerLayout::getDefault()) {
}

void CUserDataImpl::subscribeToFingerLayout(CFingerLayoutObserver* obs) {
  assert(obs);
  FingerLayoutOutput_.subscribe(obs);
}

void CUserDataImpl::setFingerLayout(CFingerLayout&& FingerLayout) {
  FingerLayoutOutput_.set(std::move(FingerLayout));
}

} // namespace NSUserDataDetail
} // namespace NSKernel
} // namespace NSApplication
