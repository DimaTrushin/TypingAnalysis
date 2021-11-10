#include "MainWindow.h"

#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QwtPlot>

namespace NSApplication {
namespace NSQt {

CMainWindow::CMainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);
  addQwtPanel();
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

QTextEdit* CMainWindow::getMainTextEdit() const {
  return ui_->textEdit_2;
}

QwtPlot* CMainWindow::getSpeedPlot() const {
  return SpeedPlot_;
}

QTableView* CMainWindow::getStatisticsTable() const {
  return ui_->tableView;
}

void CMainWindow::adjustStaticInterface() {
  adjustSplitters();
  adjustButtonGroups();
}

void CMainWindow::adjustSplitters() {
  adjustSplitter();
  adjustSplitter2();
  adjustSplitter3();
  adjustMainSplitter();
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

void CMainWindow::adjustMainSplitter() {
  ui_->splitter_4->setSizes(QList<int>() << 5000 << 5000);
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

void CMainWindow::addQwtPanel() {
  SpeedPlot_ = new QwtPlot(ui_->splitter_4);
  ui_->splitter_4->addWidget(SpeedPlot_);
}
} // namespace NSQt
} // namespace NSApplication
