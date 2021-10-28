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

private:
  void handle(const CKeyPressing& KeyPressing);
  void handle(const CKeyReleasing& KeyReleasing);

  CKeyPressingInput KeyPressingInput_;
  CKeyReleasingInput KeyReleasingInput_;
  CSeanceObservable CurrentSeanceOutput_;
  CSeanceMaker SeanceMaker_;
  CSeance CurrentSeance_;
  // TO DO
  // Add CurrentSeance
  // Add flush method to move RawSessions from SeanceMaker to CurrentSeance
  // Add LoadedSeances, to load seances from files
  // Add NewSeance Input, to load new seances
  // Add CurrentSession Output
  // Add SeancesDescription Output, for GUI
  // Add Set Current Session Control, for GUI
};
} // namespace NSSeanceManagerDetail

using CSeanceManager =
    NSLibrary::CModelWrapper<NSSeanceManagerDetail::CSeanceManagerImpl>;

// class CSeanceManager {

// public:
//  using CSeanceManagerImpl = NSSeanceManagerDetail::CSeanceManagerImpl;
//  CSeanceManager();
//  ~CSeanceManager();

//  CSeanceManagerImpl* operator->() const;

// private:
//  std::unique_ptr<CSeanceManagerImpl> Impl_;
//};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEMANAGER_H
