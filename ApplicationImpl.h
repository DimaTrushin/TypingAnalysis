#ifndef NSAPPLICATION_CAPPLICATIONIMPL_H
#define NSAPPLICATION_CAPPLICATIONIMPL_H

#include "Interface/KeyboardShutter.h"
#include "ApplicationGUI.h"
#include "ApplicationKernel.h"


namespace NSApplication {

class CApplicationImpl
  : protected CApplicationKernel, protected CApplicationGUI {
  using CKeyboardShutter = NSInterface::CKeyboardShutter;
public:
  CApplicationImpl();
private:
  CKeyboardShutter KeyboardShutter_;
};

} // NSApplication

#endif // NSAPPLICATION_CAPPLICATIONIMPL_H
