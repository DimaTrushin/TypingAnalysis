#ifndef NSAPPLICATION_CAPPLICATIONIMPL_H
#define NSAPPLICATION_CAPPLICATIONIMPL_H

#include "ApplicationGUI.h"
#include "ApplicationKernel.h"
#include "Interface/FileActionController.h"
#include "Interface/FileActionKeyboardBlocker.h"
#include "Interface/KeyboardShutter.h"
#include "Interface/ModifiersModeController.h"
#include "Interface/SeanceViewController.h"
#include "Interface/SessionFlusher.h"
#include "Interface/TextModeController.h"

namespace NSApplication {

class CApplicationImpl : protected CApplicationKernel,
                         protected CApplicationGUI {
  using CKeyboardShutter = NSInterface::CKeyboardShutter;
  using CSessionFlusher = NSInterface::CSessionFlusher;
  using CSeanceViewController = NSInterface::CSeanceViewController;
  using CTextModeController = NSInterface::CTextModeController;
  using CFileActionController = NSInterface::CFileActionController;
  using CFileActionKeyboardBlocker = NSInterface::CFileActionKeyboardBlocker;
  using CModifiersModeController = NSInterface::CModifiersModeController;

public:
  CApplicationImpl();

private:
  CKeyboardShutter KeyboardShutter_;
  CSessionFlusher SessionFlusher_;
  CSeanceViewController SeanceViewController_;
  CTextModeController TextModeController_;
  CFileActionController FileActionController_;
  CFileActionKeyboardBlocker FileActionKeyboardBlocker_;
  CModifiersModeController ModifiersModeController_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONIMPL_H
