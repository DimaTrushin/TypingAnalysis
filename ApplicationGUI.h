#ifndef NSAPPLICATION_CAPPLICATIONGUI_H
#define NSAPPLICATION_CAPPLICATIONGUI_H

#include "Interface/KeySchemePlotter.h"
#include "Interface/Plotter.h"
#include "Interface/SeanceView.h"
#include "Interface/StatisticsView.h"
#include "Interface/TextModeView.h"
#include "Interface/TextPrinter.h"
#include "Qt/MainWindow.h"

#include <memory>

#ifdef KEYBOARD_HANDLER_DEBUG
#include "AppDebug/KeyboardHandlerDebugOut.h"
#endif

namespace NSApplication {

class CApplicationGUI {
  using CSeanceView = NSInterface::CSeanceView;
  using CTextModeView = NSInterface::CTextModeView;
  using CTextPrinter = NSInterface::CTextPrinter;
  using CPlotter = NSInterface::CSpeedPlotter;
  using CStatisticsView = NSInterface::CStatisticsView;
  using CKeySchemePlotter = NSInterface::CKeySchemePlotter;
  using CFileMenu = NSInterface::CFileMenu;
  using CModifiersMenu = NSInterface::CModifiersMenu;

public:
  CApplicationGUI();

protected:
  NSQt::CMainWindow* mainWindow();

private:
  NSQt::CMainWindow AppWindow_;

protected:
  CSeanceView MainSeanceView_;
  CTextModeView TextModeView_;
  CTextPrinter MainTextPrinter_;
  CPlotter SpeedPlotter_;
  CStatisticsView StatisticsView_;
  CKeySchemePlotter KeySchemePlotter_;
  CFileMenu FileMenu_;
  CModifiersMenu ModifiersMenu_;

#ifdef KEYBOARD_HANDLER_DEBUG
  NSAppDebug::CKeyboardHandlerDebugOut KeyboardHandlerOut_ = mainWindow();
#endif
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONGUI_H
