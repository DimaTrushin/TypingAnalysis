#include "KeyboardHandler.h"

#include "KeyboardListener.h"
#include "ListenerExceptionHandler.h"
#include "QtLoopException.h"

namespace NSApplication {
namespace NSKeyboard {

CQtMessagesRegistrator::CQtMessagesRegistrator() {
  qRegisterMetaType<CKeyPressing>();
  qRegisterMetaType<CKeyReleasing>();
}

CKeyboardHandler::CKeyboardHandler() {
  CQtLoopException QtExceptions;
  QtExceptions->connectSignal(this, &CKeyboardHandler::quit);

  CAnyKillerPromise killerPromise;
  CAnyKillerFuture killerFuture = killerPromise.get_future();
  ListenerThread_ = CWorkerThread(run, std::move(killerPromise), this);
  // Need Timeout here
  KeyboardKiller_ = killerFuture.get();
}

CKeyboardHandler::~CKeyboardHandler() {
  stopListener();
}

void CKeyboardHandler::activate(CBlockerID::CType Blocker) {
  BlockerFlag_ &= static_cast<CBlockerID::CType>(-1) ^ Blocker;
}

void CKeyboardHandler::deactivate(CBlockerID::CType Blocker) {
  BlockerFlag_ |= Blocker;
}

bool CKeyboardHandler::isActive() const {
  return BlockerFlag_ == CBlockerID::Active;
}

void CKeyboardHandler::subscribeToKeyPressing(
    CKeyboardHandler::CKeyPressingObserver* Observer) {
  assert(Observer);
  KeyPressingOut_.subscribe(Observer);
}

void CKeyboardHandler::subscribeToKeyReleasing(
    CKeyboardHandler::CKeyReleasingObserver* Observer) {
  assert(Observer);
  KeyReleasingOut_.subscribe(Observer);
}

void CKeyboardHandler::onKeyPressing(const CKeyPressing& KeyPressing) {
  if (isActive())
    KeyPressingOut_.set(KeyPressing);
}

void CKeyboardHandler::onKeyReleasing(const CKeyReleasing& KeyReleasing) {
  if (isActive())
    KeyReleasingOut_.set(KeyReleasing);
}

void CKeyboardHandler::onKeyboardException(const CQtException& message) {
  Q_EMIT quit(message);
}

void CKeyboardHandler::stopListener() const noexcept {
  assert(KeyboardKiller_.isDefined());
  KeyboardKiller_->stopListener();
}

// This code is executed on the worker thread
void CKeyboardHandler::run(CAnyKillerPromise killerPromise,
                           CKeyboardHandler* KeyboardHandler) {
  try {
    CKeyboardListener KeyboardListener(std::move(killerPromise),
                                       KeyboardHandler);
    KeyboardListener.exec();
  } catch (...) {
    CListenerExceptionHandler React(KeyboardHandler);
  }
}

} // namespace NSKeyboard
} // namespace NSApplication
