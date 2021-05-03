#ifndef NSAPPLICATION_NSKEYBOARD_CRAWINPUTHOOK_H
#define NSAPPLICATION_NSKEYBOARD_CRAWINPUTHOOK_H

#include "MessageWindow.h"

#include <QDebug>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

template<LPCWSTR TClassName, WNDPROC TWndProc>
class CRawInputHook : public CMessageWindow<TClassName, TWndProc> {
  using CBase = CMessageWindow<TClassName, TWndProc>;

public:
  using CWinContext = typename CBase::CWinContext;
  CRawInputHook() {
    RAWINPUTDEVICE LowLevelKeyboard;
    LowLevelKeyboard.usUsagePage = 0x01;
    LowLevelKeyboard.usUsage = 0x06;
    LowLevelKeyboard.dwFlags = RIDEV_INPUTSINK;
    LowLevelKeyboard.hwndTarget = CBase::hwnd();
    if (RegisterRawInputDevices(&LowLevelKeyboard, 1,
                                sizeof(LowLevelKeyboard)) == FALSE)
      throw std::runtime_error("Cannot register RAWINPUT");
  }

  ~CRawInputHook() {
    RAWINPUTDEVICE LowLevelKeyboard;
    LowLevelKeyboard.usUsagePage = 0x01;
    LowLevelKeyboard.usUsage = 0x06;
    LowLevelKeyboard.dwFlags = RIDEV_REMOVE;
    LowLevelKeyboard.hwndTarget = nullptr;
    if (RegisterRawInputDevices(&LowLevelKeyboard, 1,
                                sizeof(LowLevelKeyboard)) == FALSE)
      qDebug() << "Cannot unregister RAWINPUT";
  }
};

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CRAWINPUTHOOK_H
