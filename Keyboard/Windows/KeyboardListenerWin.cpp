#include "KeyboardListenerWin.h"

#include "Keyboard/KeyboardHandler.h"
#include "Keyboard/RawKeyEvent.h"

#include <QDebug>


namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {


CKeyboardListenerWinImpl::CKeyboardListenerWinImpl(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler) {
  provideHookToListener();
  killerPromise.set_value(CKiller(hwnd()));
  // TO DO
  // Should I divide it into layers?
  connect(this, &CKeyboardListenerWinImpl::KeyboardMessage,
          KeyboardHandler, &CKeyboardHandler::onKeyboardMessage,
          Qt::ConnectionType::QueuedConnection);
}

CKeyboardListenerWinImpl::~CKeyboardListenerWinImpl() {
  disconnect(this, &CKeyboardListenerWinImpl::KeyboardMessage, nullptr, nullptr);
}

int CKeyboardListenerWinImpl::exec() {
  CMessageStatus Status;
  MSG CurrentMessage;
  while ((Status = getMessage(&CurrentMessage)) != Quit) {
    if (Status == Error)
      handleError(&CurrentMessage);
    else
      dispatchMessage(&CurrentMessage);
  }
  return exitCode(&CurrentMessage);
}

CKeyboardListenerWinImpl::CMessageStatus CKeyboardListenerWinImpl::getMessage(MSG* CurrentMessage) {
  return ::GetMessage(CurrentMessage, hwnd(), 0, 0);
}

void CKeyboardListenerWinImpl::dispatchMessage(MSG* CurrentMessage) {
  ::TranslateMessage(CurrentMessage);
  ::DispatchMessage(CurrentMessage);
}

void CKeyboardListenerWinImpl::handleError(MSG* CurrentMessage) {
  (void)CurrentMessage;
  DWORD ErrorCode = GetLastError();
  std::string ErrorMessage = "KeyboardListener error with code = ";
  ErrorMessage += std::to_string(ErrorCode);
  throw std::runtime_error(ErrorMessage.c_str());
}

int CKeyboardListenerWinImpl::exitCode(MSG* CurrentMessage) const {
  return static_cast<int>(CurrentMessage->wParam);
}

void CKeyboardListenerWinImpl::provideHookToListener() {
  ::SetWindowLongPtr(hwnd(), GWLP_USERDATA, LONG_PTR(this));
}

CKeyboardListenerWinImpl* CKeyboardListenerWinImpl::getKeyboardListener(HWND hwnd) {
  return reinterpret_cast<CKeyboardListenerWinImpl*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

LRESULT CKeyboardListenerWinImpl::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
  switch (message) {
  case WM_STOP_LISTENING:
    ::PostQuitMessage(0);
    break;
  case WM_INPUT:
    // TO DO
    // This function does not support several instances of Listeners
    // Should I implement a singleton tracking all instances?
    getKeyboardListener(hwnd)->HandleRawInput(lparam);
    break;
  default:
    ;
  }
  return ::DefWindowProc(hwnd, message, wparam, lparam);
}

void CKeyboardListenerWinImpl::HandleRawInput(LPARAM lParam) {
  qDebug() << "Handle lParam";
  const RAWKEYBOARD& KeyboardData = RawInputReader_.getKeyboardData(lParam);
  // TO DO
  // Translate the KeyboardData to CRawKeyEvent
  // and send it to the required object

  qDebug() << "VKey = " << KeyboardData.VKey;
  qDebug() << "Flags = " << KeyboardData.Flags;
  // TO DO
  emit KeyboardMessage(CRawKeyEvent("Message"));
}

HWND& CKeyboardListenerWinImpl::hwnd() {
  return KeyboardHook_.hwnd();
}


CKeyboardListenerWin::CKeyboardListenerWin(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler)
  : KeyboardListener_(getKeyboardUPtr(std::move(killerPromise), KeyboardHandler)) {
}

int CKeyboardListenerWin::exec() {
  if (isDefined())
    return KeyboardListener_->exec();
  return 0;
}

bool CKeyboardListenerWin::isDefined() const {
  return static_cast<bool>(KeyboardListener_);
}

CKeyboardListenerWin::CKeyboardUPtr CKeyboardListenerWin::getKeyboardUPtr(
  CAnyKillerPromise killerPromise,
  CKeyboardHandler* KeyboardHandler) {
  return std::make_unique<CKeyboardListenerWinImpl>(std::move(killerPromise), KeyboardHandler);
}


CKiller::CKiller(HWND MessageWindow)
  :  MessageWindow_(MessageWindow) {
  assert(MessageWindow_ != NULL);
}

void CKiller::stopListener() const {
  assert(MessageWindow_ != NULL);
  if (MessageWindow_ != NULL)
    ::PostMessage(MessageWindow_, WM_STOP_LISTENING, 0, 0);
}

} // NSWindows
} // NSKeyboard
} // NSApplication
