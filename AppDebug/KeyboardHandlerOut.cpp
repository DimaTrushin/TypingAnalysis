#include "KeyboardHandlerOut.h"
#include "KeyboardHandlerAccess.h"

namespace NSAppDebug {

CKeyboardHandlerOut::CKeyboardHandlerOut(QWidget* parent)
  : Window_(std::make_unique<QMainWindow>(parent)),
    CentralWidget_(std::make_unique<QWidget>(Window_.get())),
    Layout_(std::make_unique<QVBoxLayout>(CentralWidget_.get())),
    TextEdit_(std::make_unique<QTextEdit>(CentralWidget_.get())),
    KeyPressingInput_([this](const CKeyPressing& KeyEvent) {
  outputKeyPressing(KeyEvent);
}),
KeyReleasingInput_([this](const CKeyReleasing& KeyEvent) {
  outputKeyReleasing(KeyEvent);
}) {
  setupUI();
  subscribeToKeyboardHandler();
  Window_->show();
}

void CKeyboardHandlerOut::setupUI() {
  Window_->setWindowTitle("CKeyboardHandler Debug");
  Window_->resize(1200, 600);
  TextEdit_->setFontFamily("Courier New");
  TextEdit_->setReadOnly(true);
  Layout_->addWidget(TextEdit_.get());
  Window_->setCentralWidget(CentralWidget_.get());
}

void CKeyboardHandlerOut::subscribeToKeyboardHandler() {
  NSApplication::CKeyboardHandlerAccess KeyboardHandler;
  KeyboardHandler->subscribeToKeyPressing(&KeyPressingInput_);
  KeyboardHandler->subscribeToKeyReleasing(&KeyReleasingInput_);
}

void CKeyboardHandlerOut::outputKeyPressing(
  const CKeyboardHandlerOut::CKeyPressing& KeyEvent) {
  QString Text = QString("Press \tKeID = 0x%1\tKeyPos = 0x%2\ttime = %3 ms\tsymb = %4\tlbl = %5")
                 .arg(KeyEvent.KeyID, 2, 16)
                 .arg(KeyEvent.KeyPosition, 2, 16)
                 .arg(KeyEvent.PressingTime.toMilliSecondsF(), 10)
                 .arg(KeyEvent.KeyText, 2)
                 .arg(KeyEvent.KeyLabel);
  TextEdit_->append(Text);
}

void CKeyboardHandlerOut::outputKeyReleasing(
  const CKeyboardHandlerOut::CKeyReleasing& KeyEvent) {
  QString Text = QString("Release\tKeID = 0x%1\tKeyPos = 0x%2\ttime = %3 ms")
                 .arg(KeyEvent.KeyID, 2, 16)
                 .arg(KeyEvent.KeyPosition, 2, 16)
                 .arg(KeyEvent.ReleasingTime.toMilliSecondsF(), 10);
  TextEdit_->append(Text);
}

} // NSAppDebug
