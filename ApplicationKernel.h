#ifndef NSAPPLICATION_CAPPLICATIONKERNEL_H
#define NSAPPLICATION_CAPPLICATIONKERNEL_H

#include "ApplicationGlobals.h"

namespace NSApplication {

class CApplicationKernel : protected CApplicationGlobals {
public:
  CApplicationKernel();
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONKERNEL_H
