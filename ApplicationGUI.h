#ifndef NSAPPLICATION_CAPPLICATIONGUI_H
#define NSAPPLICATION_CAPPLICATIONGUI_H

#include "Qt/MainWindow.h"

#include <memory>

namespace NSApplication {

class CApplicationGUI {
public:
  CApplicationGUI();

protected:
  NSQt::CMainWindow* mainWindow();

private:
  NSQt::CMainWindow AppWindow_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONGUI_H
