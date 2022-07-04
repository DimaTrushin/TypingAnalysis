#include "ApplicationGUI.h"

namespace NSApplication {

CApplicationGUI::CApplicationGUI()
    : MainSeanceView_(AppWindow_.getSeanceView()),
      TextModeView_(AppWindow_.getTextModeInitData()),
      MainTextPrinter_(AppWindow_.getMainTextEdit()),
      SpeedPlotter_(AppWindow_.getSpeedPlot()),
      StatisticsView_(AppWindow_.getStatisticsTable()),
      KeySchemePlotter_(AppWindow_.getKeySchemePlot()),
      FileMenu_(AppWindow_.getFileMenu()),
      ModifiersMenu_(AppWindow_.getModifiersMenuInit()) {
  // TO DO
  // should probably move this to CApplicationImpl or CApplication
  AppWindow_.show();
}

NSQt::CMainWindow* CApplicationGUI::mainWindow() {
  return &AppWindow_;
}

} // namespace NSApplication
