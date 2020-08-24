#ifndef NSAPPDEBUG_CKEYBOARDHANDLEROUT_H
#define NSAPPDEBUG_CKEYBOARDHANDLEROUT_H

#include "Library/Observer/Observer.h"
#include "Keyboard/RawKeyEvent.h"

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

#include <memory>

namespace NSAppDebug {

class CKeyboardHandlerOut {
  using CKeyPressing = NSApplication::NSKeyboard::CKeyPressing;
  using CKeyReleasing = NSApplication::NSKeyboard::CKeyReleasing;
  using CKeyPressingInput = NSLibrary::CHotInput<CKeyPressing>;
  using CKeyReleasingInput = NSLibrary::CHotInput<CKeyReleasing>;
public:
  CKeyboardHandlerOut(QWidget* parent);

private:
  void setupUI();
  void subscribeToKeyboardHandler();

  void outputKeyPressing(const CKeyPressing&);
  void outputKeyReleasing(const CKeyReleasing&);

  std::unique_ptr<QMainWindow> Window_;
  std::unique_ptr<QWidget> CentralWidget_;
  std::unique_ptr<QVBoxLayout> Layout_;
  std::unique_ptr<QTextEdit> TextEdit_;
  CKeyPressingInput KeyPressingInput_;
  CKeyReleasingInput KeyReleasingInput_;
};

} // NSAppDebug

#endif // NSAPPDEBUG_CKEYBOARDHANDLEROUT_H
