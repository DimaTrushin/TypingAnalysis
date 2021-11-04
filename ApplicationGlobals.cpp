#include "ApplicationGlobals.h"

#include "AppStatusAccess.h"
#include "KeyboardHandlerAccess.h"
#include "ParallelModuleAccess.h"
#include "SimdDetectorAccess.h"
#include "TimerAccess.h"

namespace NSApplication {

CApplicationGlobals::CApplicationGlobals() {
  CTimerInit MainTimer;
  CKeyboardHandlerInit MainKeyboardHandler;
  CAppStatusInit MainAppStatusAccessorInit;
  CSimdDetectorInit MainSimdDetector;
  CParallelInit MainComputerInit(NSCompute::EParallelMode::Ppl);
}

} // namespace NSApplication
