#ifndef NSAPPLICATION_NSKERNEL_CTEXTDATA_H
#define NSAPPLICATION_NSKERNEL_CTEXTDATA_H

#include <memory>

#include "Kernel/Session.h"
#include "Kernel/TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

struct CTextData {
  std::reference_wrapper<const CSession> Session;
  std::reference_wrapper<const CTextDataTree> TextTree;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTDATA_H
