#include "KeyboardListener.h"

namespace NSApplication {
namespace NSKeyboard {

CKeyboardListener::CKeyboardListener(CAnyKillerPromise killerPromise,
                                     CKeyboardHandler* KeyboardHandler)
    : KeyboardListener_(
          getKeyboardUPtr(std::move(killerPromise), KeyboardHandler)) {
}

int CKeyboardListener::exec() {
  if (isDefined())
    return KeyboardListener_->exec();
  return 0;
}

bool CKeyboardListener::isDefined() const {
  return static_cast<bool>(KeyboardListener_);
}

CKeyboardListener::CKeyboardUPtr
CKeyboardListener::getKeyboardUPtr(CAnyKillerPromise killerPromise,
                                   CKeyboardHandler* KeyboardHandler) {
  return std::make_unique<CKeyboardListenerImpl>(std::move(killerPromise),
                                                 KeyboardHandler);
}

} // namespace NSKeyboard
} // namespace NSApplication
