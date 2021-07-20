#include "SeanceManagerDebugGUI.h"

#include "Qt/MainWindow.h"

#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QTreeView>

namespace NSAppDebug {

CSeanceManagerDebugGUI::CSeanceManagerDebugGUI(CMainWindow* MainWindow)
    : Window_(std::make_unique<QMainWindow>()),
      CentralWidget_(new QWidget(Window_.get())),
      Layout_(new QHBoxLayout(CentralWidget_)),
      TextEdit_(new QTextEdit(CentralWidget_)),
      TreeView_(new QTreeView(CentralWidget_)) {
  QObject::connect(MainWindow, &CMainWindow::closeMainWindow, Window_.get(),
                   &QMainWindow::close);
  setupUI();
  Window_->show();
}

CSeanceManagerDebugGUI::~CSeanceManagerDebugGUI() = default;

QTextEdit* CSeanceManagerDebugGUI::Text() {
  return TextEdit_;
}

QTreeView* CSeanceManagerDebugGUI::TreeView() {
  return TreeView_;
}

void CSeanceManagerDebugGUI::setupUI() {
  Window_->setWindowTitle("CSeanceManager Debug");
  Window_->resize(400, 600);
  TextEdit_->setFontFamily("Courier New");
  TextEdit_->setReadOnly(true);
  Layout_->addWidget(TextEdit_);
  Layout_->addWidget(TreeView_);
  Window_->setCentralWidget(CentralWidget_);
}

} // namespace NSAppDebug
