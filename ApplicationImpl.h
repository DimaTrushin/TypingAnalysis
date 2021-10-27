#ifndef NSAPPLICATION_CAPPLICATIONIMPL_H
#define NSAPPLICATION_CAPPLICATIONIMPL_H

#include "ApplicationGUI.h"
#include "ApplicationKernel.h"
#include "Interface/KeyboardShutter.h"
#include "Interface/SeanceViewController.h"
#include "Interface/SessionFlusher.h"

namespace NSApplication {

class CApplicationImpl : protected CApplicationKernel,
                         protected CApplicationGUI {
  using CKeyboardShutter = NSInterface::CKeyboardShutter;
  using CSessionFlusher = NSInterface::CSessionFlusher;
  using CSeanceViewController = NSInterface::CSeanceViewController;

public:
  CApplicationImpl();

private:
  CKeyboardShutter KeyboardShutter_;
  CSessionFlusher SessionFlusher_;
  CSeanceViewController SeanceViewController_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONIMPL_H
