#ifndef NSAPPLICATION_NSKERNEL_CSEANCEVIEWDATA_H
#define NSAPPLICATION_NSKERNEL_CSEANCEVIEWDATA_H

#include "Kernel/Seance.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {

struct CSeanceViewData {
  using Index = int;
  static constexpr const Index kNotSelected = -1;

  std::reference_wrapper<const CSeance> Seance;
  Index CurrentSession;
};
} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEVIEWDATA_H
