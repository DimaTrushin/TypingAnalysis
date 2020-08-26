#ifndef NSAPPLICATION_NSKERNEL_CSEANCEMANAGERIMPL_H
#define NSAPPLICATION_NSKERNEL_CSEANCEMANAGERIMPL_H

#include "Library/Observer/Observer.h"
#include "SeanceMaker.h"


namespace NSApplication {
namespace NSKernel {

class CSeanceManagerImpl {
  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CKeyReleasing = NSKeyboard::CKeyReleasing;
  using CKeyPressingInput = NSLibrary::CHotInput<CKeyPressing>;
  using CKeyReleasingInput = NSLibrary::CHotInput<CKeyReleasing>;
public:
  CSeanceManagerImpl();

  NSLibrary::CObserver<CKeyPressing>* pressingInput();
  NSLibrary::CObserver<CKeyReleasing>* releasingInput();

private:
  void handle(const CKeyPressing& KeyPressing);
  void handle(const CKeyReleasing& KeyReleasing);

  CKeyPressingInput KeyPressingInput_;
  CKeyReleasingInput KeyReleasingInput_;
  CSeanceMaker SeanceMaker_;

  // TO DO
  // Add CurrentSeance
  // Add flush method to move RawSessions from SeanceMaker to CurrentSeance
  // Add LoadedSeances, to load seances from files
  // Add NewSeance Input, to load new seances
  // Add CurrentSession Output
  // Add SeancesDescription Output, for GUI
  // Add Set Current Session Control, for GUI
};

} // NSKernel
} // NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEMANAGERIMPL_H
