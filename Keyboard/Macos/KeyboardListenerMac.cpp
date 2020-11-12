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
  // Set killerPromise
  //killerPromise.set_value(CKiller(...));

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


CKeyboardListenerMac::CKeyboardListenerMac(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler)
  : KeyboardListener_(getKeyboardUPtr(std::move(killerPromise), KeyboardHandler)) {
}

int CKeyboardListenerMac::exec() {
  if (isDefined())
    return KeyboardListener_->exec();
  return 0;
}

bool CKeyboardListenerMac::isDefined() const {
  return static_cast<bool>(KeyboardListener_);
}

CKeyboardListenerMac::CKeyboardUPtr CKeyboardListenerMac::getKeyboardUPtr(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler) {
  return std::make_unique<CKeyboardListenerMacImpl>(std::move(killerPromise), KeyboardHandler);
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
