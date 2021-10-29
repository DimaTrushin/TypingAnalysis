#ifndef NSAPPLICATION_NSKERNEL_CSESSIONTOTREECONVERTER_H
#define NSAPPLICATION_NSKERNEL_CSESSIONTOTREECONVERTER_H

#include "Kernel/TextDataTree.h"
#include "TimeApp.h"

namespace NSApplication {
namespace NSKernel {

class CSession;

class CSessionToTreeConverter {
public:
  void convert(const CSession& Source, CTextDataTree* Target);

private:
  CTime LastPressedTime_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSESSIONTOTREECONVERTER_H
