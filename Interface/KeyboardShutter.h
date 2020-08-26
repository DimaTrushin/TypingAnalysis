#ifndef NSAPPLICATION_NSINTERFACE_CKEYBOARDSHUTTER_H
#define NSAPPLICATION_NSINTERFACE_CKEYBOARDSHUTTER_H

#include "Library/Observer/Observer.h"
#include "Qt/AppState.h"

#include <memory>


namespace NSApplication {

namespace NSKeyboard {
class CKeyboardHandler;
} // NSKeyboard

namespace NSInterface {


// TO DO
// I am not sure that this is an appropriate place to define the class
class CKeyboardShutter {
  using EAppState = NSQt::EAppState;
  using CStateObserverInput = NSLibrary::CHotInput<EAppState>;
  using CStateObserver = NSLibrary::CObserver<EAppState>;
  using CKeyboardHandler = NSKeyboard::CKeyboardHandler;
public:
  CKeyboardShutter(CKeyboardHandler*);

  CStateObserver* input();
private:
  void switchKeyboardHandler(EAppState);

  CKeyboardHandler* KeyboardHandler_;
  std::unique_ptr<CStateObserverInput> StateObserver_;
};

} // NSInterface
} // NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CKEYBOARDSHUTTER_H
