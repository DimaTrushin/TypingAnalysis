#ifndef NSAPPLICATION_CAPPLICATIONIMPL_H
#define NSAPPLICATION_CAPPLICATIONIMPL_H

#include "ApplicationKernel.h"
#include "ApplicationGUI.h"

namespace NSApplication {

class CApplicationImpl
  : protected CApplicationKernel, protected CApplicationGUI {
public:
  CApplicationImpl();
};

} // NSApplication

#endif // NSAPPLICATION_CAPPLICATIONIMPL_H
