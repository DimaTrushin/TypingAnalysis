#include "KeyboardShutter.h"

#include "Keyboard/KeyboardHandler.h"

namespace NSApplication {
namespace NSInterface {

CKeyboardShutter::CKeyboardShutter(CKeyboardHandler* KeyboardHandler)
    : KeyboardHandler_(KeyboardHandler),
      StateObserver_(std::make_unique<CStateObserverInput>(
          [this](EAppState State) { switchKeyboardHandler(State); })) {
}

CKeyboardShutter::CStateObserver* CKeyboardShutter::input() {
  return StateObserver_.get();
}

void CKeyboardShutter::switchKeyboardHandler(EAppState State) {
  if (State == EAppState::Active)
    KeyboardHandler_->deactivate();
  if (State == EAppState::Inactive)
    KeyboardHandler_->activate();
}

} // namespace NSInterface
} // namespace NSApplication
