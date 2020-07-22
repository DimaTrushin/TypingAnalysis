#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERWIN_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERWIN_H

#include "Keyboard/AnyKeyboardKiller.h"
#include "KeyPositionWin.h"
#include "RawInputHook.h"
#include "RawInputReader.h"

#include <future>
#include <QObject>


namespace NSApplication {
namespace NSKeyboard {

class CKeyboardHandler;
class CRawKeyEvent;

namespace NSWindows {

class CKeyboardListenerWinImpl : public QObject {
  Q_OBJECT

  friend class CKiller;
  using CMessageStatus = BOOL;
public:
  using CAnyKillerPromise = std::promise<CAnyKeyboardKiller>;
  CKeyboardListenerWinImpl(CAnyKillerPromise, CKeyboardHandler*);
  ~CKeyboardListenerWinImpl();

signals:
  void KeyboardMessage(const CRawKeyEvent&);
public:
  int exec();
private:
  CMessageStatus getMessage(MSG* CurrentMessage);
  void dispatchMessage(MSG* CurrentMessage);
  void handleError(MSG* CurrentMessage);
  int exitCode(MSG* CurrentMessage) const;

  void provideHookToListener();
  static CKeyboardListenerWinImpl* getKeyboardListener(HWND);
  static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
  void HandleRawInput(LPARAM lParam);

  static constexpr CMessageStatus Error = -1;
  static constexpr CMessageStatus Quit = 0;
  static constexpr UINT WM_STOP_LISTENING = WM_APP;
  static constexpr const wchar_t kWindowClassName_[] = L"KeyboardListenerWndClass";

  using CWinRawInputHook = CRawInputHook<kWindowClassName_, WndProc>;
  using CWinContext = CWinRawInputHook::CWinContext;

  HWND& hwnd();
  CWinRawInputHook KeyboardHook_;
  CRawInputReader RawInputReader_;
  NSWindows::CKeyPositionWin KeyPosition_;
};


class CKeyboardListenerWin {
  using CKeyboardUPtr = std::unique_ptr<CKeyboardListenerWinImpl>;
public:
  using CAnyKillerPromise = typename CKeyboardListenerWinImpl::CAnyKillerPromise;

  CKeyboardListenerWin(CAnyKillerPromise, CKeyboardHandler*);
  int exec();
  bool isDefined() const;

private:
  CKeyboardUPtr getKeyboardUPtr(CAnyKillerPromise, CKeyboardHandler*);
  CKeyboardUPtr KeyboardListener_;
};


// The object provides a way to shut down the listener
class CKiller {
public:
  CKiller() = default;
  CKiller(HWND);
  void stopListener() const;

private:
  static constexpr UINT WM_STOP_LISTENING = CKeyboardListenerWinImpl::WM_STOP_LISTENING;
  HWND MessageWindow_;
};

} // NSWindows
} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERWIN_H
