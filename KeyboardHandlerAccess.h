#ifndef NSAPPLICATION_CKEYBOARDHANDLERACCESS_H
#define NSAPPLICATION_CKEYBOARDHANDLERACCESS_H

#include "Keyboard/KeyboardHandler.h"
#include "Library/Singleton/AnyGlobalAccess.h"

namespace NSApplication {
namespace NSKeyboardHandlerDetail {

namespace nl = NSLibrary;
namespace nk = NSKeyboard;

class CMainKeyboardHandler;

class CKeyboardHandlerInitializer
    : ::NSLibrary::CAnyGlobalInitializer<nk::CKeyboardHandler, CMainKeyboardHandler> {
  using CBase =
      ::NSLibrary::CAnyGlobalInitializer<nk::CKeyboardHandler, CMainKeyboardHandler>;

public:
  using CBase::CBase;
};

class CKeyboardHandlerAccess
    : public ::NSLibrary::CAnyGlobalAccess<nk::CKeyboardHandler, CMainKeyboardHandler> {
};
} // namespace NSKeyboardHandlerDetail

using CKeyboardHandlerInit =
    NSKeyboardHandlerDetail::CKeyboardHandlerInitializer;
using CKeyboardHandlerAccess = NSKeyboardHandlerDetail::CKeyboardHandlerAccess;

} // namespace NSApplication

#endif // NSAPPLICATION_CKEYBOARDHANDLERACCESS_H
