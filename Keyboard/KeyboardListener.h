#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENER_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENER_H

#include <QObject>

#ifdef Q_OS_WIN
#include "Windows/KeyboardListenerWin.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSKeyboardListenerDetail {
using CKeyboardListenerImpl = NSWindows::CKeyboardListenerWinImpl;

} // NSKeyboardListenerDetail
} // NSKeyboard
} // NSApplication
#endif // Q_OS_WIN

#ifdef Q_OS_MACOS
#include "KeyboardListenerMac.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSKeyboardListenerDetail {
using CKeyboardListenerImpl = NSMacos::CKeyboardListenerMacImpl;

} // NSKeyboardListenerDetail
} // NSKeyboard
} // NSApplication
#endif // Q_OS_MACOS

#ifdef Q_OS_LINUX
#include "KeyboardListenerLinux.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSKeyboardListenerDetail {
using CKeyboardListenerImpl = NSLinux::CKeyboardListenerLinImpl;

} // NSKeyboardListenerDetail
} // NSKeyboard
} // NSApplication
#endif // Q_OS_LINUX


namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing;
struct CKeyReleasing;

class CKeyboardHandler;

class CKeyboardListener {
  using CKeyboardListenerImpl = NSKeyboardListenerDetail::CKeyboardListenerImpl;
  using CKeyboardUPtr = std::unique_ptr<CKeyboardListenerImpl>;
public:
  using CAnyKillerPromise = typename CKeyboardListenerImpl::CAnyKillerPromise;

  CKeyboardListener(CAnyKillerPromise, CKeyboardHandler*);
  int exec();
  bool isDefined() const;

private:
  CKeyboardUPtr getKeyboardUPtr(CAnyKillerPromise, CKeyboardHandler*);
  CKeyboardUPtr KeyboardListener_;
};

} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENER_H
