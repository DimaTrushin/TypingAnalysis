#ifndef NSAPPDEBUG_CKEYBOARDHANDLERDEBUGOUT_H
#define NSAPPDEBUG_CKEYBOARDHANDLERDEBUGOUT_H

#include "Keyboard/RawKeyEvent.h"
#include "Library/Observer/Observer.h"

#include <memory>


QT_BEGIN_NAMESPACE
class QTextEdit;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSQt {
class CMainWindow;
}
}

namespace NSAppDebug {

class CKeyboardHandlerDebugGUI;

namespace NSKeyboardHandlerOutDetail {

class CKeyboardHandlerDebugOutImpl {
  using CKeyPressing = NSApplication::NSKeyboard::CKeyPressing;
  using CKeyReleasing = NSApplication::NSKeyboard::CKeyReleasing;
  using CKeyPressingInput = NSLibrary::CHotInput<CKeyPressing>;
  using CKeyReleasingInput = NSLibrary::CHotInput<CKeyReleasing>;

  using CMainWindow = NSApplication::NSQt::CMainWindow;
public:
  CKeyboardHandlerDebugOutImpl(CMainWindow* MainWindow);
  ~CKeyboardHandlerDebugOutImpl();

private:
  void subscribeToKeyboardHandler();

  void outputKeyPressing(const CKeyPressing&);
  void outputKeyReleasing(const CKeyReleasing&);

  std::unique_ptr<CKeyboardHandlerDebugGUI> ui_;
  CKeyPressingInput KeyPressingInput_;
  CKeyReleasingInput KeyReleasingInput_;
};
} // NSKeyboardHandlerOutDetail

class CKeyboardHandlerDebugOut {
  using CMainWindow = NSApplication::NSQt::CMainWindow;
  using CKeyboardHandlerOutImpl = NSKeyboardHandlerOutDetail::CKeyboardHandlerDebugOutImpl;
public:
  CKeyboardHandlerDebugOut(CMainWindow* MainWindow);
private:
  std::unique_ptr<CKeyboardHandlerOutImpl> Impl_;
};

} // NSAppDebug

#endif // NSAPPDEBUG_CKEYBOARDHANDLERDEBUGOUT_H
