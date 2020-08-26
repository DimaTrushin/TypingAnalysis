#include "ApplicationImpl.h"

#include "AppStatusAccess.h"
#include "KeyboardHandlerAccess.h"

namespace NSApplication {

CApplicationImpl::CApplicationImpl()
  : KeyboardShutter_(CKeyboardHandlerAccess().operator->()) {
  CAppStatusAccess AppStatus;
  AppStatus->subscribeToAppState(KeyboardShutter_.input());
}

} // NSApplication
