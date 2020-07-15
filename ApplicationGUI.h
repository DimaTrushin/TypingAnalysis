#ifndef NSAPPLICATION_CAPPLICATIONGUI_H
#define NSAPPLICATION_CAPPLICATIONGUI_H

#include "Qt/MainWindow.h"
#include <memory>

namespace NSApplication {

class CApplicationGUI {
public:
  CApplicationGUI();
private:
  NSQt::MainWindow AppWindow_;
};

} // NSApplication

#endif // NSAPPLICATION_CAPPLICATIONGUI_H
