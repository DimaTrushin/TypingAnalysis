#include "MainWindow.h"

#include "ui_MainWindow.h"

#include "qwt_plot.h"
#include <QActionGroup>
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
  Q_EMIT closeMainWindow();
  QMainWindow::closeEvent(Event);
}

QTreeView* CMainWindow::getSeanceView() const {
  return ui_->treeView;
}

CMainWindow::CTextModeInitData CMainWindow::getTextModeInitData() const {
  return {ui_->buttonGroup, ui_->groupBox, ui_->radioButton, ui_->radioButton_2,
          ui_->radioButton_3};
}

QButtonGroup* CMainWindow::getTextButtonGroup() const {
  return ui_->buttonGroup;
}

QPlainTextEdit* CMainWindow::getMainTextEdit() const {
  return ui_->plainTextEdit_2;
}

QFrame* CMainWindow::getSpeedPlotterParent() const {
  return ui_->frame_8;
}

QTableView* CMainWindow::getStatisticsTable() const {
  return ui_->tableView;
}

QFrame* CMainWindow::getKeySchemeParent() const {
  return ui_->frame_5;
}

QMenu* CMainWindow::getFileMenu() const {
  return ui_->menuFile;
}

CMainWindow::CModifiersModeInitData CMainWindow::getModifiersMenuInit() const {
  return {ui_->menuModifiers, ui_->menuShift, ui_->menuCtrl, ui_->menuAlt};
}

QMenu* CMainWindow::getLanguageMenu() const {
  return ui_->menuLanguage;
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

void CMainWindow::adjustButtonGroups() {
  adjustButtonGroup();
}

void CMainWindow::adjustButtonGroup() {
  ui_->buttonGroup->setId(ui_->radioButton, 0);
  ui_->buttonGroup->setId(ui_->radioButton_2, 1);
  ui_->buttonGroup->setId(ui_->radioButton_3, 2);
}

} // namespace NSQt
} // namespace NSApplication
