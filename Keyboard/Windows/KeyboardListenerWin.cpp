#include "KeyboardListenerWin.h"

#include "KeyIDWin.h"
#include "Keyboard/KeyboardHandler.h"
#include "Keyboard/RawKeyEvent.h"
#include "TimerAccess.h"
#include "WinKeyboardApi.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

CKeyboardListenerWinImpl::CKeyboardListenerWinImpl(
    CAnyKillerPromise killerPromise, CKeyboardHandler* KeyboardHandler) {
  provideHookToListener();
  killerPromise.set_value(CKiller(hwnd()));
  // TO DO
  // Should I divide it into layers?
  connect(this, &CKeyboardListenerWinImpl::KeyPressing, KeyboardHandler,
          &CKeyboardHandler::onKeyPressing,
          Qt::ConnectionType::QueuedConnection);
  connect(this, &CKeyboardListenerWinImpl::KeyReleasing, KeyboardHandler,
          &CKeyboardHandler::onKeyReleasing,
          Qt::ConnectionType::QueuedConnection);
}

CKeyboardListenerWinImpl::~CKeyboardListenerWinImpl() {
  disconnect(this, &CKeyboardListenerWinImpl::KeyPressing, nullptr, nullptr);
  disconnect(this, &CKeyboardListenerWinImpl::KeyReleasing, nullptr, nullptr);
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

CKeyboardListenerWinImpl::CMessageStatus
CKeyboardListenerWinImpl::getMessage(MSG* CurrentMessage) {
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

CKeyboardListenerWinImpl*
CKeyboardListenerWinImpl::getKeyboardListener(HWND hwnd) {
  return reinterpret_cast<CKeyboardListenerWinImpl*>(
      ::GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

LRESULT CKeyboardListenerWinImpl::WndProc(HWND hwnd, UINT message,
                                          WPARAM wparam, LPARAM lparam) {
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
  default:;
  }
  return ::DefWindowProc(hwnd, message, wparam, lparam);
}

void CKeyboardListenerWinImpl::HandleRawInput(LPARAM lParam) {
  CTimerAccess Timer;
  auto Time = Timer->get();

  const RAWKEYBOARD& KeyData = RawInputReader_.getKeyboardData(lParam);

  CKeyPosition KeyPosition =
      KeyPosition_.make(KeyData.VKey, KeyData.MakeCode, KeyData.Flags);
  if (KeyPosition == CKeyPosEnum::UNKN)
    return;
  CKeyID KeyID = CKeyIDWin::make(KeyData.VKey, KeyData.MakeCode, KeyData.Flags);
  if (KeyID == CKeyIDEnum::Unknown || KeyID == CKeyIDEnum::Ignore)
    return;

  if (isPressing(KeyData)) {
    CKeyFlags Flags = getFlags(KeyData);
    CLabelData Label = getKeyLabel(KeyData);
    // The next function modifies the state of the KeyTextMaker_ because of the
    // dead keys. This code is fragile. Must not move this function out of if
    // statement.
    CKeyTextData KeyTextData = getKeyText(KeyData);

    Q_EMIT KeyPressing({Time, KeyPosition, KeyID, Label, KeyTextData, Flags});
  } else {
    Q_EMIT KeyReleasing({Time, KeyPosition, KeyID});
  }
}

bool CKeyboardListenerWinImpl::isPressing(const RAWKEYBOARD& KeyData) const {
  return CWinKeyboardApi::isPressing(KeyData.Flags);
}

bool CKeyboardListenerWinImpl::isReleasing(const RAWKEYBOARD& KeyData) const {
  return CWinKeyboardApi::isReleasing(KeyData.Flags);
}

CKeyTextData CKeyboardListenerWinImpl::getKeyText(const RAWKEYBOARD& KeyData) {
  return KeyTextMaker_.getText(KeyData.VKey, CWinKeyboardApi::getShifters(),
                               CWinKeyboardApi::getForegroundLayout());
}

CLabelData CKeyboardListenerWinImpl::getKeyLabel(const RAWKEYBOARD& KeyData) {
  return KeyTextMaker_.getLabel(KeyData.MakeCode, KeyData.Flags,
                                CWinKeyboardApi::getForegroundLayout());
}

CKeyboardListenerWinImpl::CKeyFlags
CKeyboardListenerWinImpl::getFlags(const RAWKEYBOARD& KeyData) {
  CKeyFlags Flags = CWinKeyboardApi::getShifters();
  if (KeyTextMaker_.isDeadKey(KeyData.VKey, CWinKeyboardApi::getShifters()))
    Flags |= CKeyFlagsEnum::DeadKey;
  return Flags;
}

HWND CKeyboardListenerWinImpl::hwnd() const {
  return KeyboardHook_.hwnd();
}

CKiller::CKiller(HWND MessageWindow) : MessageWindow_(MessageWindow) {
  assert(MessageWindow_ != NULL);
}

void CKiller::stopListener() const {
  assert(MessageWindow_ != NULL);
  if (MessageWindow_ != NULL)
    ::PostMessage(MessageWindow_, WM_STOP_LISTENING, 0, 0);
}

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication
