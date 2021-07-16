#ifndef NSAPPLICATION_CAPPLICATIONIMPL_H
#define NSAPPLICATION_CAPPLICATIONIMPL_H

#include "ApplicationGUI.h"
#include "ApplicationKernel.h"
#include "Interface/KeyboardShutter.h"
#include "Interface/SessionFlusher.h"

#ifdef SEANCE_MANAGER_DEBUG
#include "AppDebug/SeanceManagerDebugOut.h"
#endif

namespace NSApplication {

class CApplicationImpl : protected CApplicationKernel,
                         protected CApplicationGUI {
  using CKeyboardShutter = NSInterface::CKeyboardShutter;
  using CSessionFlusher = NSInterface::CSessionFlusher;

public:
  CApplicationImpl();

private:
  CKeyboardShutter KeyboardShutter_;
  CSessionFlusher SessionFlusher_;
#ifdef SEANCE_MANAGER_DEBUG
  NSAppDebug::CSeanceManagerDebugOut SeanceManagerOut_;
#endif
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONIMPL_H
