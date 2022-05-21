#include "ApplicationGlobals.h"

#include "AppStatusAccess.h"
#include "Compute/ParallelMode.h"
#include "KeyboardHandlerAccess.h"
#include "MathModuleAccess.h"
#include "ParallelModuleAccess.h"
#include "SimdDetectorAccess.h"
#include "TimerAccess.h"

namespace NSApplication {

CApplicationGlobals::CApplicationGlobals() {
  CTimerInit MainTimer;
  CKeyboardHandlerInit MainKeyboardHandler;
  CAppStatusInit MainAppStatusAccessorInit;
  CSimdDetectorInit MainSimdDetector;
  CParallelInit MainComputerInit(NSCompute::EParallelMode::Tbb);
  CMathInit MainMath(*CParallelAccess());
}

} // namespace NSApplication
