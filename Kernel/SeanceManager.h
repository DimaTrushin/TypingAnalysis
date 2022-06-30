#ifndef NSAPPLICATION_NSKERNEL_CSEANCEMANAGER_H
#define NSAPPLICATION_NSKERNEL_CSEANCEMANAGER_H

#include <memory>

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Seance.h"
#include "SeanceMaker.h"

namespace NSApplication {
namespace NSKernel {

namespace NSSeanceManagerDetail {

class CSeanceManagerImpl {
  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CKeyReleasing = NSKeyboard::CKeyReleasing;
  using CKeyPressingInput = NSLibrary::CHotInput<CKeyPressing>;
  using CKeyReleasingInput = NSLibrary::CHotInput<CKeyReleasing>;

  using CSeanceObservable = NSLibrary::CObservable<CSeance>;
  using CSeanceGetType = typename NSLibrary::CSource<CSeance>::CGetType;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;

public:
  CSeanceManagerImpl();

  NSLibrary::CObserver<CKeyPressing>* pressingInput();
  NSLibrary::CObserver<CKeyReleasing>* releasingInput();

  void subscribeToCurrentSeance(CSeanceObserver*);

  void makeSessions();

  void saveFile(const QString& Path);
  void loadFile(const QString& Path);

private:
  void handle(const CKeyPressing& KeyPressing);
  void handle(const CKeyReleasing& KeyReleasing);

  CKeyPressingInput KeyPressingInput_;
  CKeyReleasingInput KeyReleasingInput_;
  CSeanceObservable CurrentSeanceOutput_;
  CSeanceMaker SeanceMaker_;
  CSeance CurrentSeance_;
};
} // namespace NSSeanceManagerDetail

using CSeanceManager =
    NSLibrary::CModelWrapper<NSSeanceManagerDetail::CSeanceManagerImpl>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEMANAGER_H
