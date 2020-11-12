#include "KeyboardListenerLin.h"

#include "Keyboard/KeyboardHandler.h"


namespace NSApplication {
namespace NSKeyboard {
namespace NSLinux {

CKeyboardListenerLinImpl::CKeyboardListenerLinImpl(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler) {
  // TO DO
  // Set the Listener

  // TO DO
  // Set killerPromise
  //killerPromise.set_value(CKiller(...));

  connect(this, &CKeyboardListenerLinImpl::KeyPressing,
          KeyboardHandler, &CKeyboardHandler::onKeyPressing,
          Qt::ConnectionType::QueuedConnection);
  connect(this, &CKeyboardListenerLinImpl::KeyReleasing,
          KeyboardHandler, &CKeyboardHandler::onKeyReleasing,
          Qt::ConnectionType::QueuedConnection);
}

CKeyboardListenerLinImpl::~CKeyboardListenerLinImpl() {
  disconnect(this, &CKeyboardListenerLinImpl::KeyPressing, nullptr, nullptr);
  disconnect(this, &CKeyboardListenerLinImpl::KeyReleasing, nullptr, nullptr);
}

int CKeyboardListenerLinImpl::exec() {
  // TO DO
  // Message loop
}


CKeyboardListenerLin::CKeyboardListenerLin(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler)
  : KeyboardListener_(getKeyboardUPtr(std::move(killerPromise), KeyboardHandler)) {
}

int CKeyboardListenerLin::exec() {
  if (isDefined())
    return KeyboardListener_->exec();
  return 0;
}

bool CKeyboardListenerLin::isDefined() const {
  return static_cast<bool>(KeyboardListener_);
}

CKeyboardListenerLin::CKeyboardUPtr CKeyboardListenerLin::getKeyboardUPtr(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler) {
  return std::make_unique<CKeyboardListenerLinImpl>(std::move(killerPromise), KeyboardHandler);
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

} // NSLinux
} // NSKeyboard
} // NSApplication
