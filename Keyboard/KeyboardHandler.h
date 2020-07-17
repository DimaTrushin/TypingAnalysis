#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H

#include "Library/StlExtension/ThreadDetachable.h"
#include "Qt/QtLoopExceptionHandler.h"
#include "AnyKeyboardKiller.h"

#include <future>


namespace NSApplication {
namespace NSKeyboard {

class CRawKeyEvent;

// A system dependent keyboard listener lives in an independent thread
// all exceptions of the listener are sent to corresponding slot
// The listener dies on any exception or error

class CQtMessagesRegistrator : public QObject {
  Q_OBJECT
public:
  CQtMessagesRegistrator();
protected:
  ~CQtMessagesRegistrator() = default;
};


class CKeyboardHandler : public CQtMessagesRegistrator {
  Q_OBJECT

  using CAnyKillerPromise = std::promise<CAnyKeyboardKiller>;
  using CAnyKillerFuture = std::future<CAnyKeyboardKiller>;
  using CWorkerThread = NSLibrary::CThreadDetachable;
  using CQtException = NSQt::CQtException;
public:
  CKeyboardHandler();
  ~CKeyboardHandler();

  void activate();
  void deactivate();
signals:
  void quit(const CQtException&);
public slots:
  void onKeyboardMessage(const CRawKeyEvent&);
  void onKeyboardException(const CQtException&);

private:
  void stopListener() const noexcept;
  static void run(CAnyKillerPromise, CKeyboardHandler*);

  CWorkerThread ListenerThread_;
  CAnyKeyboardKiller KeyboardKiller_;
  bool isActive_ = true;
};

} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H
