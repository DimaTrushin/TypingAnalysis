#ifndef NSAPPLICATION_NSKEYBOARD_CMESSAGEWINDOW_H
#define NSAPPLICATION_NSKEYBOARD_CMESSAGEWINDOW_H

#include <Windows.h>
#include <stdexcept>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

template<LPCWSTR TClassName, WNDPROC TWndProc>
class CWindowClassEx {
public:
  static const WNDCLASSEX& get() {
    static WNDCLASSEX wc = getWndClass();
    return wc;
  }

private:
  static WNDCLASSEX getWndClass() {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(wc);
    wc.hInstance = ::GetModuleHandle(nullptr);
    wc.lpfnWndProc = TWndProc;
    wc.lpszClassName = TClassName;

    return wc;
  }
};

template<LPCWSTR TClassName, WNDPROC TWndProc>
class CRegisteredWindowClassEx {
  using CWindowClassEx = CWindowClassEx<TClassName, TWndProc>;

public:
  static const WNDCLASSEX& get() {
    static CRegister Now;
    return CWindowClassEx::get();
  }

  static LPCWSTR className() {
    return get().lpszClassName;
  }

  static HINSTANCE hInstance() {
    return get().hInstance;
  }

private:
  class CRegister {
  public:
    CRegister() {
      if (!::RegisterClassEx(&CWindowClassEx::get()))
        throw std::runtime_error(kRegisterErrorMessage_);
    }

    ~CRegister() {
      ::UnregisterClass(className(), hInstance());
    }

  private:
    static LPCWSTR className() {
      return CWindowClassEx::get().lpszClassName;
    }

    static HINSTANCE hInstance() {
      return CWindowClassEx::get().hInstance;
    }

    static constexpr const char* kRegisterErrorMessage_ =
        "Cannot register Window Class";
  };
};

template<LPCWSTR TClassName, WNDPROC TWndProc>
class CMessageWindow {
public:
  using CWinContext = CRegisteredWindowClassEx<TClassName, TWndProc>;
  CMessageWindow()
      : MessageWindow_(::CreateWindowEx(0, CWinContext::className(), TEXT(""),
                                        0, 0, 0, 0, 0, HWND_MESSAGE, NULL,
                                        CWinContext::hInstance(), NULL)) {
    if (!MessageWindow_)
      throw std::runtime_error(kCreationErrorMessage_);
  }

  ~CMessageWindow() {
    ::DestroyWindow(MessageWindow_);
  }

  HWND hwnd() const {
    return MessageWindow_;
  }

private:
  static constexpr const char* kCreationErrorMessage_ =
      "Cannot create Window Class";
  HWND MessageWindow_;
};

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CMESSAGEWINDOW_H
