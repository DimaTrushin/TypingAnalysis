#include "KeyboardListenerLin.h"

#include "Keyboard/KeyboardHandler.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSLinux {

CKeyboardListenerLinImpl::CKeyboardListenerLinImpl(
    CAnyKillerPromise killerPromise, CKeyboardHandler* KeyboardHandler) {
  // TO DO
  // Set the Listener

  // TO DO
  // Set killerPromise to a non-trivial one
  killerPromise.set_value(CKiller());

  connect(this, &CKeyboardListenerLinImpl::KeyPressing, KeyboardHandler,
          &CKeyboardHandler::onKeyPressing,
          Qt::ConnectionType::QueuedConnection);
  connect(this, &CKeyboardListenerLinImpl::KeyReleasing, KeyboardHandler,
          &CKeyboardHandler::onKeyReleasing,
          Qt::ConnectionType::QueuedConnection);
}

CKeyboardListenerLinImpl::~CKeyboardListenerLinImpl() {
  disconnect(this, &CKeyboardListenerLinImpl::KeyPressing, nullptr, nullptr);
  disconnect(this, &CKeyboardListenerLinImpl::KeyReleasing, nullptr, nullptr);
}

int CKeyboardListenerLinImpl::exec() {
  // TO DO
  // Message loop
  return 0;
}

// TO DO
// a specific ctor of CKiller
// CKiller::CKiller(...) {
//
//}

void CKiller::stopListener() const {
  // TO DO
  // Implementation details
  // Send message to CKeyboardListenerLinImpl to stop listening
}

} // namespace NSLinux
} // namespace NSKeyboard
} // namespace NSApplication
