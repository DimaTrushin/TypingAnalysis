#include "MainWindow.h"

#include "ui_MainWindow.h"

#include <QCloseEvent>

namespace NSApplication {
namespace NSQt {

CMainWindow::CMainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>())
#ifdef KEYBOARD_HANDLER_DEBUG
      ,
      KeyboardHandlerOut_(this)
#endif
{
  ui_->setupUi(this);
}

void CMainWindow::closeEvent(QCloseEvent* Event) {
  emit closeMainWindow();
  QMainWindow::closeEvent(Event);
}

CMainWindow::~CMainWindow() = default;
} // namespace NSQt
} // namespace NSApplication
