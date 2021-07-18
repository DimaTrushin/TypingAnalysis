#include "MainWindow.h"

#include "ui_MainWindow.h"

#include <QCloseEvent>

namespace NSApplication {
namespace NSQt {

CMainWindow::CMainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);
}

void CMainWindow::closeEvent(QCloseEvent* Event) {
  emit closeMainWindow();
  QMainWindow::closeEvent(Event);
}

CMainWindow::~CMainWindow() = default;
} // namespace NSQt
} // namespace NSApplication
