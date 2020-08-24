#include "MainWindow.h"

#include "ui_MainWindow.h"

namespace NSApplication {
namespace NSQt {

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui_(std::make_unique<Ui::MainWindow>())
#ifdef KEYBOARD_HANDLER_DEBUG
  , KeyboardHandlerOut_(std::make_unique<NSAppDebug::CKeyboardHandlerOut>(this))
#endif
{
  ui_->setupUi(this);
}

MainWindow::~MainWindow() = default;
} // NSQt
} // NSApplication
