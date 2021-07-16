#include "ApplicationGUI.h"

namespace NSApplication {

CApplicationGUI::CApplicationGUI() {
  // TO DO
  // should probably move this to CApplicationImpl or CApplication
  AppWindow_.show();
}

NSQt::CMainWindow* CApplicationGUI::mainWindow() {
  return &AppWindow_;
}

} // namespace NSApplication
