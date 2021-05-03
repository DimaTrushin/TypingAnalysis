#include "QtLoopExceptionHandler.h"
#include "ExceptionHandler.h"

#include <QApplication>

namespace NSApplication {
namespace NSQt {

CQtLoopExceptionHandler::CQtLoopExceptionHandler() {
  qRegisterMetaType<CQtException>();
  connect(this, &CQtLoopExceptionHandler::quit, qApp, &QApplication::quit,
          Qt::ConnectionType::QueuedConnection);
}

void CQtLoopExceptionHandler::handleException(const CQtException& Exception) {
  try {
    throw Exception;
  } catch (...) {
    CExceptionHandler React;
  }
  emit quit();
}

} // namespace NSQt
} // namespace NSApplication
