#include "ApplicationGlobals.h"
#include "TimerAccess.h"

namespace NSApplication {

CApplicationGlobals::CApplicationGlobals() {
  CTimerInit MainTimer;
}

} // NSApplication
