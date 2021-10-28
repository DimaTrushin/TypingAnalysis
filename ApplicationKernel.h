#ifndef NSAPPLICATION_CAPPLICATIONKERNEL_H
#define NSAPPLICATION_CAPPLICATIONKERNEL_H

#include "ApplicationGlobals.h"
#include "Kernel/SeanceManager.h"
#include "Kernel/SessionSelector.h"
#include "Kernel/TextModule.h"

namespace NSApplication {

class CApplicationKernel : protected CApplicationGlobals {
  using CSeanceManager = NSKernel::CSeanceManager;
  using CSessionSelector = NSKernel::CSessionSelector;
  using CTextModule = NSKernel::CTextModule;

public:
  CApplicationKernel();

protected:
  CSeanceManager SeanceManager_;
  CSessionSelector SessionSelector_;
  CTextModule TextModule_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONKERNEL_H
