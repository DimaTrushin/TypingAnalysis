#ifndef NSAPPLICATION_CAPPLICATIONKERNEL_H
#define NSAPPLICATION_CAPPLICATIONKERNEL_H

#include "ApplicationGlobals.h"
#include "Kernel/SeanceManager.h"

namespace NSApplication {

class CApplicationKernel : protected CApplicationGlobals {
  using CSeanceManager = NSKernel::CSeanceManager;

public:
  CApplicationKernel();

protected:
  CSeanceManager SeanceManager_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONKERNEL_H
