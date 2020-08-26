#ifndef NSAPPLICATION_CAPPLICATIONIMPL_H
#define NSAPPLICATION_CAPPLICATIONIMPL_H

#include "Interface/KeyboardShutter.h"
#include "Interface/SessionFlusher.h"
#include "ApplicationGUI.h"
#include "ApplicationKernel.h"


namespace NSApplication {

class CApplicationImpl
  : protected CApplicationKernel, protected CApplicationGUI {
  using CKeyboardShutter = NSInterface::CKeyboardShutter;
  using CSessionFlusher = NSInterface::CSessionFlusher;
public:
  CApplicationImpl();

private:
  CKeyboardShutter KeyboardShutter_;
  CSessionFlusher SessionFlusher_;
};

} // NSApplication

#endif // NSAPPLICATION_CAPPLICATIONIMPL_H
