#ifndef NSAPPLICATION_NSKEYBOARD_CLISTENEREXCEPTIONHANDLER_H
#define NSAPPLICATION_NSKEYBOARD_CLISTENEREXCEPTIONHANDLER_H

#include "Qt/QtLoopExceptionHandler.h"

#include <QObject>

namespace NSApplication {
namespace NSKeyboard {

class CKeyboardHandler;

class CExceptionConnector : public QObject {
  Q_OBJECT
public:
  using CQtException = NSQt::CQtException;

  CExceptionConnector(CKeyboardHandler*);
  ~CExceptionConnector();

signals:
  void KeyboardException(const CQtException&);
};

class CListenerExceptionHandler : public CExceptionConnector {
  Q_OBJECT
public:
  CListenerExceptionHandler(CKeyboardHandler*);

private:
  static constexpr const char* kUnknownExceptionMsg_ = "Unknown Exception!";
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CLISTENEREXCEPTIONHANDLER_H
