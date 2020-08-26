#ifndef NSAPPLICATION_CAPPLICATIONKERNEL_H
#define NSAPPLICATION_CAPPLICATIONKERNEL_H

#include "Kernel/SeanceManager.h"
#include "ApplicationGlobals.h"


namespace NSApplication {

class CApplicationKernel : protected CApplicationGlobals {
  using CSeanceManager = NSKernel::CSeanceManager;
public:
  CApplicationKernel();
protected:
  CSeanceManager SeanceManager_;
};

} // NSApplication

#endif // NSAPPLICATION_CAPPLICATIONKERNEL_H
