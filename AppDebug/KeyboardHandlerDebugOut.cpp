#include "KeyboardHandlerDebugOut.h"

#include "AppDebug/KeyboardHandlerDebugGUI.h"

#include <QTextEdit>
#include <QVBoxLayout>

namespace NSAppDebug {
namespace NSKeyboardHandlerOutDetail {
CKeyboardHandlerDebugOutImpl::CKeyboardHandlerDebugOutImpl(
    CMainWindow* MainWindow)
    : ui_(std::make_unique<CKeyboardHandlerDebugGUI>(MainWindow)),
      KeyPressingInput_([this](const CKeyPressing& KeyEvent) {
        outputKeyPressing(KeyEvent);
      }),
      KeyReleasingInput_([this](const CKeyReleasing& KeyEvent) {
        outputKeyReleasing(KeyEvent);
      }) {
}

CKeyboardHandlerDebugOutImpl::~CKeyboardHandlerDebugOutImpl() = default;

CKeyboardHandlerDebugOutImpl::CKeyPressingObserver*
CKeyboardHandlerDebugOutImpl::keyPressingInput() {
  return &KeyPressingInput_;
}

CKeyboardHandlerDebugOutImpl::CKeyReleasingObserver*
CKeyboardHandlerDebugOutImpl::keyReleasingInput() {
  return &KeyReleasingInput_;
}

void CKeyboardHandlerDebugOutImpl::outputKeyPressing(
    const CKeyboardHandlerDebugOutImpl::CKeyPressing& KeyEvent) {
  QString Text = QString("Press \tKeID = 0x%1\t KeyPos = 0x%2\ttime = %3 "
                         "ms\tsymb = %4\tlbl = %5")
                     .arg(KeyEvent.KeyID, 2, 16, QChar('0'))
                     .arg(KeyEvent.KeyPosition, 2, 16, QChar('0'))
                     .arg(KeyEvent.Time.toMilliSecondsF(), 10)
                     .arg(KeyEvent.KeyText, 2)
                     .arg(KeyEvent.KeyLabel);
  ui_->Text()->append(Text);
}

void CKeyboardHandlerDebugOutImpl::outputKeyReleasing(
    const CKeyboardHandlerDebugOutImpl::CKeyReleasing& KeyEvent) {
  QString Text = QString("Release\tKeID = 0x%1\t KeyPos = 0x%2\ttime = %3 ms")
                     .arg(KeyEvent.KeyID, 2, 16, QChar('0'))
                     .arg(KeyEvent.KeyPosition, 2, 16, QChar('0'))
                     .arg(KeyEvent.Time.toMilliSecondsF(), 10);
  ui_->Text()->append(Text);
}
} // namespace NSKeyboardHandlerOutDetail

CKeyboardHandlerDebugOut::CKeyboardHandlerDebugOut(CMainWindow* MainWindow)
    : Impl_(std::make_unique<CKeyboardHandlerOutImpl>(MainWindow)) {
}

CKeyboardHandlerDebugOut::CKeyboardHandlerOutImpl*
CKeyboardHandlerDebugOut::operator->() {
  return Impl_.get();
}

} // namespace NSAppDebug
