#ifndef NSAPPLICATION_NSCOMPUTE_CPARALLELLIN_H
#define NSAPPLICATION_NSCOMPUTE_CPARALLELLIN_H

#include "ParallelMode.h"
#include "ParallelSerial.h"

namespace NSApplication {
namespace NSCompute {

class CParallelLin {
public:
  CParallelLin(EParallelMode Mode);

  template<class TIndex, class TFunction>
  void for_(TIndex begin, TIndex end, const TFunction& F) {
    switch (Mode_) {
    case EParallelMode::Serial:
      SerialComputer_.for_(begin, end, F);
      break;
    case EParallelMode::Ppl:
      SerialComputer_.for_(begin, end, F);
      break;
    case EParallelMode::Tbb:
      SerialComputer_.for_(begin, end, F);
      break;
    case EParallelMode::LibDispatch:
      SerialComputer_.for_(begin, end, F);
      break;
    default:
      break;
    }
  }

  void switchMode(EParallelMode Mode);

private:
  static constexpr const bool kIsSerialSupported = true;
  static constexpr const bool kIsPplSupported = false;
  static constexpr const bool kIsTbbSupported = false;
  static constexpr const bool kIsLibDispatchSupported = false;

  static constexpr const EParallelMode kDefaultMode = EParallelMode::Serial;

  CParallelSerial SerialComputer_;
  EParallelMode Mode_ = kDefaultMode;
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CPARALLELLIN_H
