#ifndef KEYBOARDLISTENER_H
#define KEYBOARDLISTENER_H

#include <QObject>

#ifdef Q_OS_WIN
#include "Windows/KeyboardListenerWin.h"

namespace NSApplication {
namespace NSKeyboard {
using CKeyboardListener = NSWindows::CKeyboardListenerWin;

} // NSKeyboard
} // NSApplication
#endif // Q_OS_WIN

//#ifdef Q_OS_MACOS
//#include "KeyboardListenerMac.h"
//using CKeyboardListener = CKeyboardListenerMac;
//#endif // Q_OS_MACOS

//#ifdef Q_OS_LINUX
//#include "KeyboardListenerLinux.h"
//using CKeyboardListener = CKeyboardListenerLinux;
//#endif // Q_OS_LINUX

#endif // KEYBOARDLISTENER_H
