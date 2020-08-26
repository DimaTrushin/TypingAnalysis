#include "SeanceManagerImpl.h"


namespace NSApplication {
namespace NSKernel {

CSeanceManagerImpl::CSeanceManagerImpl()
  : KeyPressingInput_([this](const CKeyPressing& KeyPressing) {
  handle(KeyPressing);
}),
KeyReleasingInput_([this](const CKeyReleasing& KeyReleasing) {
  handle(KeyReleasing);
}) {
}

NSLibrary::CObserver<CSeanceManagerImpl::CKeyPressing>*
CSeanceManagerImpl::pressingInput() {
  return &KeyPressingInput_;
}

NSLibrary::CObserver<CSeanceManagerImpl::CKeyReleasing>*
CSeanceManagerImpl::releasingInput() {
  return &KeyReleasingInput_;
}

void CSeanceManagerImpl::handle(const CKeyPressing& KeyPressing) {
  SeanceMaker_.add(KeyPressing);
}

void CSeanceManagerImpl::handle(const CKeyReleasing& KeyReleasing) {
  SeanceMaker_.add(KeyReleasing);
}

} // NSKernel
} // NSApplication
