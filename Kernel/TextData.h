#ifndef NSAPPLICATION_NSKERNEL_CTEXTDATA_H
#define NSAPPLICATION_NSKERNEL_CTEXTDATA_H

#include <memory>

#include "Kernel/Session.h"

namespace NSApplication {
namespace NSKernel {

struct CTextData {
  std::reference_wrapper<const CSession> Session;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTDATA_H
