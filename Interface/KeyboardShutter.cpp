#include "KeyboardShutter.h"

#include "Keyboard/KeyboardHandler.h"

namespace NSApplication {
namespace NSInterface {

namespace NSCKeyboardShutterDetail {

CKeyboardShutterImpl::CKeyboardShutterImpl(CKeyboardHandler* KeyboardHandler)
    : KeyboardHandler_(KeyboardHandler),
      StateObserver_(
          [this](EAppState State) { switchKeyboardHandler(State); }) {
}

CKeyboardShutterImpl::CStateObserver* CKeyboardShutterImpl::input() {
  return &StateObserver_;
}

void CKeyboardShutterImpl::switchKeyboardHandler(EAppState State) {
  if (State == EAppState::Active)
    KeyboardHandler_->deactivate(NSKeyboard::CKeyboardBlock::Enum::AppStatus);
  if (State == EAppState::Inactive)
    KeyboardHandler_->activate(NSKeyboard::CKeyboardBlock::Enum::AppStatus);
}

} // namespace NSCKeyboardShutterDetail

} // namespace NSInterface
} // namespace NSApplication
