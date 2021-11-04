#include "ParallelWin.h"

#include <cassert>

namespace NSApplication {
namespace NSCompute {

CParallelWin::CParallelWin(EParallelMode Mode) {
  switch (Mode) {
  case EParallelMode::Serial:
    if (kIsSerialSupported)
      Mode_ = Mode;
    break;
  case EParallelMode::Ppl:
    if (kIsPplSupported)
      Mode_ = Mode;
    break;
  case EParallelMode::Tbb:
    if (kIsTbbSupported)
      Mode_ = Mode;
    break;
  case EParallelMode::LibDispatch:
    if (kIsLibDispatchSupported)
      Mode_ = Mode;
    break;
  default:
    assert(false);
    break;
  }
}

void CParallelWin::switchMode(EParallelMode Mode) {
  switch (Mode) {
  case EParallelMode::Serial:
    if (kIsSerialSupported)
      Mode_ = Mode;
    break;
  case EParallelMode::Ppl:
    if (kIsPplSupported)
      Mode_ = Mode;
    break;
  case EParallelMode::Tbb:
    if (kIsTbbSupported)
      Mode_ = Mode;
    break;
  case EParallelMode::LibDispatch:
    if (kIsLibDispatchSupported)
      Mode_ = Mode;
    break;
  default:
    assert(false);
    break;
  }
}

} // namespace NSCompute
} // namespace NSApplication
