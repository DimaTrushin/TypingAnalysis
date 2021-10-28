#include "MainWindow.h"

#include "ui_MainWindow.h"

#include <QCloseEvent>

namespace NSApplication {
namespace NSQt {

CMainWindow::CMainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);
  adjustStaticInterface();
}

CMainWindow::~CMainWindow() = default;

void CMainWindow::closeEvent(QCloseEvent* Event) {
  emit closeMainWindow();
  QMainWindow::closeEvent(Event);
}

QTreeView* CMainWindow::getSeanceView() const {
  return ui_->treeView;
}

QButtonGroup* CMainWindow::getTextButtonGroup() const {
  return ui_->buttonGroup;
}

QButtonGroup* CMainWindow::getShiftButtonGroup() const {
  return ui_->buttonGroup_2;
}

QButtonGroup* CMainWindow::getCtrlButtonGroup() const {
  return ui_->buttonGroup_3;
}

QButtonGroup* CMainWindow::getAltButtonGroup() const {
  return ui_->buttonGroup_4;
}

void CMainWindow::adjustStaticInterface() {
  adjustSplitters();
  adjustButtonGroups();
}

void CMainWindow::adjustSplitters() {
  adjustSplitter();
  adjustSplitter2();
  adjustSplitter3();
  adjustSplitter5();
  adjustSplitter6();
}

void CMainWindow::adjustSplitter() {
  ui_->splitter->setSizes(QList<int>() << 1200 << 8800);
}

void CMainWindow::adjustSplitter2() {
  ui_->splitter_2->setSizes(QList<int>() << 8000 << 2000);
}

void CMainWindow::adjustSplitter3() {
  ui_->splitter_3->setSizes(QList<int>() << 8000 << 2000);
}

void CMainWindow::adjustSplitter5() {
  ui_->splitter_5->setSizes(QList<int>() << 8000 << 2000);
}

void CMainWindow::adjustSplitter6() {
  ui_->splitter_6->setSizes(QList<int>() << 1200 << 8800);
}

void CMainWindow::adjustButtonGroups() {
  adjustButtonGroup();
  adjustButtonGroup2();
  adjustButtonGroup3();
  adjustButtonGroup4();
}

void CMainWindow::adjustButtonGroup() {
  ui_->buttonGroup->setId(ui_->radioButton, 0);
  ui_->buttonGroup->setId(ui_->radioButton_2, 1);
  ui_->buttonGroup->setId(ui_->radioButton_3, 2);
}

void CMainWindow::adjustButtonGroup2() {
  ui_->buttonGroup_2->setId(ui_->radioButton_4, 0);
  ui_->buttonGroup_2->setId(ui_->radioButton_5, 1);
  ui_->buttonGroup_2->setId(ui_->radioButton_6, 2);
}

void CMainWindow::adjustButtonGroup3() {
  ui_->buttonGroup_3->setId(ui_->radioButton_7, 0);
  ui_->buttonGroup_3->setId(ui_->radioButton_8, 1);
  ui_->buttonGroup_3->setId(ui_->radioButton_9, 2);
}

void CMainWindow::adjustButtonGroup4() {
  ui_->buttonGroup_4->setId(ui_->radioButton_12, 0);
  ui_->buttonGroup_4->setId(ui_->radioButton_13, 1);
  ui_->buttonGroup_4->setId(ui_->radioButton_14, 2);
}

} // namespace NSQt
} // namespace NSApplication
