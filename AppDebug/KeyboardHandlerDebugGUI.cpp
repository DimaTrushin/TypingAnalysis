#include "KeyboardHandlerDebugGUI.h"

#include "Qt/MainWindow.h"

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>

namespace NSAppDebug {

CKeyboardHandlerDebugGUI::CKeyboardHandlerDebugGUI(CMainWindow* MainWindow)
    : Window_(std::make_unique<QMainWindow>()),
      CentralWidget_(new QWidget(Window_.get())),
      Layout_(new QVBoxLayout(CentralWidget_)),
      TextEdit_(new QTextEdit(CentralWidget_)) {
  QObject::connect(MainWindow, &CMainWindow::closeMainWindow, Window_.get(),
                   &QMainWindow::close);
  setupUI();
  Window_->show();
}

CKeyboardHandlerDebugGUI::~CKeyboardHandlerDebugGUI() = default;

QTextEdit* CKeyboardHandlerDebugGUI::Text() {
  return TextEdit_;
}

void CKeyboardHandlerDebugGUI::setupUI() {
  Window_->setWindowTitle("CKeyboardHandler Debug");
  Window_->resize(1200, 600);
  TextEdit_->setFontFamily("Courier New");
  TextEdit_->setReadOnly(true);
  Layout_->addWidget(TextEdit_);
  Window_->setCentralWidget(CentralWidget_);
}

} // namespace NSAppDebug
