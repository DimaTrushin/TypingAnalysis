#include "ListenerExceptionHandler.h"

#include "KeyboardHandler.h"

namespace NSApplication {
namespace NSKeyboard {

CExceptionConnector::CExceptionConnector(CKeyboardHandler* KeyboardHandler) {
  connect(this, &CExceptionConnector::KeyboardException, KeyboardHandler,
          &CKeyboardHandler::onKeyboardException,
          Qt::ConnectionType::QueuedConnection);
}

CExceptionConnector::~CExceptionConnector() {
  disconnect(this, &CExceptionConnector::KeyboardException, nullptr, nullptr);
}

CListenerExceptionHandler::CListenerExceptionHandler(
    CKeyboardHandler* KeyboardHandler)
    : CExceptionConnector(KeyboardHandler) {
  try {
    throw;
  } catch (std::exception& Exception) {
    Q_EMIT KeyboardException(CQtException(Exception.what()));
  } catch (...) {
    Q_EMIT KeyboardException(CQtException(kUnknownExceptionMsg_));
  }
}

} // namespace NSKeyboard
} // namespace NSApplication
