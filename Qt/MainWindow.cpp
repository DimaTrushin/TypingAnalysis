#include "MainWindow.h"

#include "ui_MainWindow.h"

namespace NSApplication {
namespace NSQt {

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent),
    ui_(std::make_unique<Ui::MainWindow>()),
    KeyboardHandlerOut_(std::make_unique<NSAppDebug::CKeyboardHandlerOut>(this)) {
  ui_->setupUi(this);
}

MainWindow::~MainWindow() = default;
} // NSQt
} // NSApplication
