#include "ApplicationGlobals.h"

#include "KeyboardHandlerAccess.h"
#include "TimerAccess.h"

namespace NSApplication {

CApplicationGlobals::CApplicationGlobals() {
  CTimerInit MainTimer;
  CKeyboardHandlerInit MainKeyboardHandler;
}

} // namespace NSApplication
