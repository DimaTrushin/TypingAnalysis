#ifndef NSAPPLICATION_CAPPLICATIONIMPL_H
#define NSAPPLICATION_CAPPLICATIONIMPL_H

#include "ApplicationGUI.h"
#include "ApplicationKernel.h"

namespace NSApplication {

class CApplicationImpl : protected CApplicationKernel,
                         protected CApplicationGUI {
public:
  CApplicationImpl();
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONIMPL_H
