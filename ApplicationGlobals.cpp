#include "ApplicationGlobals.h"

#include "AppStatusAccess.h"
#include "Compute/ParallelMode.h"
#include "KeyboardHandlerAccess.h"
#include "MathModuleAccess.h"
#include "ParallelModuleAccess.h"
#ifndef DISABLE_SIMD
#include "SimdDetectorAccess.h"
#endif
#include "TimerAccess.h"

namespace NSApplication {

CApplicationGlobals::CApplicationGlobals() {
  CTimerInit MainTimer;
  CKeyboardHandlerInit MainKeyboardHandler;
  CAppStatusInit MainAppStatusAccessorInit;
#ifndef DISABLE_SIMD
  CSimdDetectorInit MainSimdDetector;
#endif
  CParallelInit MainComputerInit(NSCompute::EParallelMode::Tbb);
  CMathInit MainMath(*CParallelAccess());
}

} // namespace NSApplication
