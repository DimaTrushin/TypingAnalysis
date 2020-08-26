#include "ApplicationImpl.h"

#include "AppStatusAccess.h"
#include "KeyboardHandlerAccess.h"


namespace NSApplication {

CApplicationImpl::CApplicationImpl()
  : KeyboardShutter_(CKeyboardHandlerAccess().operator->()),
    SessionFlusher_(SeanceManager_.operator->()) {
  CAppStatusAccess AppStatus;
  AppStatus->subscribeToAppState(KeyboardShutter_.input());
  AppStatus->subscribeToAppState(SessionFlusher_.input());
}

} // NSApplication
