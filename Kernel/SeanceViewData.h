#ifndef NSAPPLICATION_NSKERNEL_CSEANCEVIEWDATA_H
#define NSAPPLICATION_NSKERNEL_CSEANCEVIEWDATA_H

#include <memory>

#include "Kernel/Seance.h"

namespace NSApplication {
namespace NSKernel {

struct CSeanceViewData {
  using Index = int64_t;
  static constexpr const Index kNotSelected = -1ll;

  std::reference_wrapper<const CSeance> Seance;
  Index CurrentSession;
};
} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEVIEWDATA_H
