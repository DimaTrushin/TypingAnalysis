#include "KeyboardListenerMac.h"

#include "Keyboard/KeyboardHandler.h"


namespace NSApplication {
namespace NSKeyboard {
namespace NSMacos {

CKeyboardListenerMacImpl::CKeyboardListenerMacImpl(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler) {
  // TO DO
  // Set the Listener

  // TO DO
  // Set killerPromise to a non-trivial one
  killerPromise.set_value(CKiller());

  connect(this, &CKeyboardListenerMacImpl::KeyPressing,
          KeyboardHandler, &CKeyboardHandler::onKeyPressing,
          Qt::ConnectionType::QueuedConnection);
  connect(this, &CKeyboardListenerMacImpl::KeyReleasing,
          KeyboardHandler, &CKeyboardHandler::onKeyReleasing,
          Qt::ConnectionType::QueuedConnection);
}

CKeyboardListenerMacImpl::~CKeyboardListenerMacImpl() {
  disconnect(this, &CKeyboardListenerMacImpl::KeyPressing, nullptr, nullptr);
  disconnect(this, &CKeyboardListenerMacImpl::KeyReleasing, nullptr, nullptr);
}

int CKeyboardListenerMacImpl::exec() {
  // TO DO
  // Message loop
}


// TO DO
// a specific ctor of CKiller
//CKiller::CKiller(...) {
//
//}

void CKiller::stopListener() const {
  // TO DO
  // Implementation details
  // Send message to CKeyboardListenerLinImpl to stop listening
}

} // NSMacos
} // NSKeyboard
} // NSApplication
