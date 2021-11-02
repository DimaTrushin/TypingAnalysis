#include "ApplicationGlobals.h"

#include "AppStatusAccess.h"
#include "KeyboardHandlerAccess.h"
#include "SimdDetectorAccess.h"
#include "TimerAccess.h"

namespace NSApplication {

CApplicationGlobals::CApplicationGlobals() {
  CTimerInit MainTimer;
  CKeyboardHandlerInit MainKeyboardHandler;
  CAppStatusInit MainAppStatusAccessorInit;
  CSimdDetectorInit MainSimdDetector;
}

} // namespace NSApplication
