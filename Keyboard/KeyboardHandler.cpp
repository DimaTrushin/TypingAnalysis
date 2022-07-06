#include "KeyboardHandler.h"

#include "KeyboardListener.h"
#include "LabelMaker.h"
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

void CKeyboardHandler::activate(CKeyboardBlock::Enum Blocker) {
  Block_.activate(Blocker);
}

void CKeyboardHandler::deactivate(CKeyboardBlock::Enum Blocker) {
  Block_.deactivate(Blocker);
}

bool CKeyboardHandler::isActive() const {
  return Block_.isActive();
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
  CKeyPressing Key = KeyPressing;
  if (Key.KeyLabel.Size == 0)
    Key.KeyLabel = CLabelMaker::make(KeyPressing.KeyID);
  if (isActive() && hasSymbolOrLabel(Key))
    KeyPressingOut_.set(Key);
  handleUserBlock(Key);
}

void CKeyboardHandler::onKeyReleasing(const CKeyReleasing& KeyReleasing) {
  if (isActive())
    KeyReleasingOut_.set(KeyReleasing);
  handleUserBlock(KeyReleasing);
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

bool CKeyboardHandler::hasSymbolOrLabel(const CKeyPressing& Key) {
  return Key.KeyText.Size > 0 || Key.KeyLabel.Size > 0;
}

void CKeyboardHandler::handleUserBlock(const CKeyPressing& KeyPressing) {
  if (BlockHistory_.has_value()) {
    // TO DO
    // Should make the combination of keys adjustable
    if (BlockHistory_->KeyID == CKeyIDEnum::F8 &&
        KeyPressing.KeyID == CKeyIDEnum::F9)
      Block_.switchBlock(CKeyboardBlock::Enum::UserBlock);
  }
  BlockHistory_ = KeyPressing;
}

void CKeyboardHandler::handleUserBlock(const CKeyReleasing& KeyReleasing) {
  if (BlockHistory_.has_value()) {
    if (BlockHistory_->KeyID == KeyReleasing.KeyID)
      BlockHistory_.reset();
  }
}
} // namespace NSKeyboard
} // namespace NSApplication
