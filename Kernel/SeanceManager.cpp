#include "SeanceManager.h"

#include <QDebug>

namespace NSApplication {
namespace NSKernel {

namespace NSSeanceManagerDetail {

CSeanceManagerImpl::CSeanceManagerImpl()
    : KeyPressingInput_(
          [this](const CKeyPressing& KeyPressing) { handle(KeyPressing); }),
      KeyReleasingInput_(
          [this](const CKeyReleasing& KeyReleasing) { handle(KeyReleasing); }),
      CurrentSeanceOutput_(
          [this]() -> CSeanceGetType { return CurrentSeance_; }) {
}

NSLibrary::CObserver<CSeanceManagerImpl::CKeyPressing>*
CSeanceManagerImpl::pressingInput() {
  return &KeyPressingInput_;
}

NSLibrary::CObserver<CSeanceManagerImpl::CKeyReleasing>*
CSeanceManagerImpl::releasingInput() {
  return &KeyReleasingInput_;
}

void CSeanceManagerImpl::subscribeToCurrentSeance(CSeanceObserver* observer) {
  CurrentSeanceOutput_.subscribe(observer);
}

void CSeanceManagerImpl::makeSessions() {
  if (SeanceMaker_.transferTo(&CurrentSeance_))
    CurrentSeanceOutput_.notify();
}

void CSeanceManagerImpl::handle(const CKeyPressing& KeyPressing) {
  SeanceMaker_.add(KeyPressing);
}

void CSeanceManagerImpl::handle(const CKeyReleasing& KeyReleasing) {
  SeanceMaker_.add(KeyReleasing);
}
} // namespace NSSeanceManagerDetail

} // namespace NSKernel
} // namespace NSApplication
