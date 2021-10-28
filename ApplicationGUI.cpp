#include "ApplicationGUI.h"

namespace NSApplication {

CApplicationGUI::CApplicationGUI()
    : MainSeanceView_(AppWindow_.getSeanceView()),
      TextModeView_(
          AppWindow_.getTextButtonGroup(), AppWindow_.getShiftButtonGroup(),
          AppWindow_.getCtrlButtonGroup(), AppWindow_.getAltButtonGroup()) {
  // TO DO
  // should probably move this to CApplicationImpl or CApplication
  AppWindow_.show();
}

NSQt::CMainWindow* CApplicationGUI::mainWindow() {
  return &AppWindow_;
}

} // namespace NSApplication
