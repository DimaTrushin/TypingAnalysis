#ifndef NSAPPLICATION_NSCOMPUTE_CPARALLELWIN_H
#define NSAPPLICATION_NSCOMPUTE_CPARALLELWIN_H

#include "ParallelMode.h"
#include "ParallelSerial.h"
#include "ParallelTbb.h"

#ifdef _MSC_VER
#include "ParallelPpl.h"
#endif

namespace NSApplication {
namespace NSCompute {

class CParallelWin {
public:
  CParallelWin(EParallelMode Mode);

  template<class TIndex, class TFunction>
  void for_(TIndex begin, TIndex end, const TFunction& F) {
    switch (Mode_) {
    case EParallelMode::Serial:
      SerialComputer_.for_(begin, end, F);
      break;
    case EParallelMode::Ppl:
#ifdef _MSC_VER
      PplComputer_.for_(begin, end, F);
#else
      SerialComputer_.for_(begin, end, F);
#endif
      break;
    case EParallelMode::Tbb:
      TbbComputer_.for_(begin, end, F);
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
#ifdef _MSC_VER
  static constexpr const bool kIsPplSupported = true;
#else
  static constexpr const bool kIsPplSupported = false;
#endif
  static constexpr const bool kIsTbbSupported = true;
  static constexpr const bool kIsLibDispatchSupported = false;

#ifdef _MSC_VER
  static constexpr const EParallelMode kDefaultMode = EParallelMode::Ppl;
#else
  static constexpr const EParallelMode kDefaultMode = EParallelMode::Serial;
#endif

  CParallelSerial SerialComputer_;
#ifdef _MSC_VER
  CParallelPpl PplComputer_;
#endif
  CParallelTbb TbbComputer_;
  EParallelMode Mode_ = kDefaultMode;
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CPARALLELWIN_H
