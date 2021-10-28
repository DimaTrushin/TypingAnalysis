#ifndef NSAPPLICATION_NSINTERFACE_CKEYBOARDSHUTTER_H
#define NSAPPLICATION_NSINTERFACE_CKEYBOARDSHUTTER_H

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Qt/AppState.h"

#include <memory>

namespace NSApplication {
namespace NSKeyboard {
class CKeyboardHandler;
} // namespace NSKeyboard

namespace NSInterface {
namespace NSCKeyboardShutterDetail {
class CKeyboardShutterImpl {
  using EAppState = NSQt::EAppState;
  using CStateObserverInput = NSLibrary::CHotInput<EAppState>;
  using CStateObserver = NSLibrary::CObserver<EAppState>;
  using CKeyboardHandler = NSKeyboard::CKeyboardHandler;

public:
  CKeyboardShutterImpl(CKeyboardHandler*);

  CStateObserver* input();

private:
  void switchKeyboardHandler(EAppState);

  CKeyboardHandler* KeyboardHandler_;
  CStateObserverInput StateObserver_;
};

} // namespace NSCKeyboardShutterDetail

using CKeyboardShutter = NSLibrary::CControllerWrapper<
    NSCKeyboardShutterDetail::CKeyboardShutterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CKEYBOARDSHUTTER_H
