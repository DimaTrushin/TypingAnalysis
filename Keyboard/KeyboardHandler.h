#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H

#include "AnyKeyboardKiller.h"
#include "KeyboardBlock.h"
#include "Library/Observer2/Observer.h"
#include "Qt/QtLoopExceptionHandler.h"
#include "RawKeyEvent.h"

#include <future>

namespace NSApplication {
namespace NSKeyboard {

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
  using CWorkerThread = std::thread;
  using CQtException = NSQt::CQtException;
  using CKeyPressingOut = NSLibrary::CObservableData<CKeyPressing>;
  using CKeyReleasingOut = NSLibrary::CObservableData<CKeyReleasing>;
  using CKeyPressingObserver = NSLibrary::CObserver<CKeyPressing>;
  using CKeyReleasingObserver = NSLibrary::CObserver<CKeyReleasing>;

  using CPressingHistory = std::optional<CKeyPressing>;

public:
  CKeyboardHandler();
  ~CKeyboardHandler();

  void activate(CKeyboardBlock::Enum Blocker);
  void deactivate(CKeyboardBlock::Enum Blocker);

  bool isActive() const;

  void subscribeToKeyPressing(CKeyPressingObserver* Observer);
  void subscribeToKeyReleasing(CKeyReleasingObserver* Observer);

Q_SIGNALS:
  void quit(const CQtException&);
public Q_SLOTS:
  void onKeyPressing(const CKeyPressing&);
  void onKeyReleasing(const CKeyReleasing&);
  void onKeyboardException(const CQtException&);

private:
  void stopListener() const noexcept;
  static void run(CAnyKillerPromise, CKeyboardHandler*);

  void correctLabel(CKeyPressing*);
  bool hasSymbolOrLabel(const CKeyPressing&);
  void handleUserBlock(const CKeyPressing&);
  void handleUserBlock(const CKeyReleasing&);

  CWorkerThread ListenerThread_;
  CAnyKeyboardKiller KeyboardKiller_;
  CKeyPressingOut KeyPressingOut_;
  CKeyReleasingOut KeyReleasingOut_;
  CKeyboardBlock Block_;
  CPressingHistory BlockHistory_;
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H
