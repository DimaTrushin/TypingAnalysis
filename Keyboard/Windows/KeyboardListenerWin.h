#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERWIN_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERWIN_H

#include "KeyPositionWin.h"
#include "KeyTextMaker.h"
#include "Keyboard/AnyKeyboardKiller.h"
#include "RawInputHook.h"
#include "RawInputReader.h"

#include <QObject>
#include <future>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing;
struct CKeyReleasing;

class CKeyboardHandler;

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
  void KeyPressing(const CKeyPressing&);
  void KeyReleasing(const CKeyReleasing&);

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

  bool isPressing(const RAWKEYBOARD& KeyData) const;
  bool isReleasing(const RAWKEYBOARD& KeyData) const;
  QString getKeyText(const RAWKEYBOARD& KeyData);
  QChar getKeyLabel(const RAWKEYBOARD& KeyData);

  static constexpr CMessageStatus Error = -1;
  static constexpr CMessageStatus Quit = 0;
  static constexpr UINT WM_STOP_LISTENING = WM_APP;
  static constexpr const wchar_t kWindowClassName_[] =
      L"KeyboardListenerWndClass";

  using CWinRawInputHook = CRawInputHook<kWindowClassName_, WndProc>;
  using CWinContext = CWinRawInputHook::CWinContext;

  HWND hwnd() const;
  CWinRawInputHook KeyboardHook_;
  CRawInputReader RawInputReader_;
  CKeyPositionWin KeyPosition_;
  CKeyTextMaker KeyTextMaker_;
};

// The object provides a way to shut down the listener
class CKiller {
public:
  CKiller() = default;
  CKiller(HWND);
  void stopListener() const;

private:
  static constexpr UINT WM_STOP_LISTENING =
      CKeyboardListenerWinImpl::WM_STOP_LISTENING;
  HWND MessageWindow_;
};

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERWIN_H
