#include "MainWindow.h"

#include "ui_MainWindow.h"

#include "SpeedPlot.h"
#include <QActionGroup>
#include <QCloseEvent>

namespace NSApplication {
namespace NSQt {

CMainWindow::CMainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);
  addQwtPlotPanel();
  addQwtPlotAdjusters();
  addQwtKeyScheme();
  adjustStaticInterface();
  adjustMenu();
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

QwtPlot* CMainWindow::getSpeedPlot() const {
  return SpeedPlot_;
}

QTableView* CMainWindow::getStatisticsTable() const {
  return ui_->tableView;
}

QwtPlot* CMainWindow::getKeySchemePlot() const {
  return KeySchemePlot_;
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

void CMainWindow::adjustMenu() {
  connect(ui_->radioButton, &QRadioButton::toggled,
          ui_->menuModifiers->menuAction(), &QAction::setDisabled);
  adjustMenu(ui_->menuShift, &ShiftActions_);
  adjustMenu(ui_->menuCtrl, &CtrlActions_);
  adjustMenu(ui_->menuAlt, &AltActions_);
}

void CMainWindow::adjustMenu(QMenu* menu,
                             std::unique_ptr<QActionGroup>* Group) {
  *Group = std::make_unique<QActionGroup>(this);
  auto Actions = menu->actions();
  for (auto Action : Actions)
    (*Group)->addAction(Action);
  Actions[0]->setChecked(true);
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

void CMainWindow::addQwtPlotPanel() {
  SpeedPlot_ = new CSpeedPlot(ui_->frame_8);
  ui_->gridLayout->addWidget(SpeedPlot_, 0, 1);
}

void CMainWindow::addQwtKeyScheme() {
  KeySchemePlot_ = new QwtPlot(ui_->frame_5);
  ui_->verticalLayout_9->addWidget(KeySchemePlot_);
}

void CMainWindow::addQwtPlotAdjusters() {
  connect(ui_->verticalSlider, &QSlider::valueChanged, SpeedPlot_,
          &CSpeedPlot::adjustVerticalScale);
  connect(ui_->horizontalSlider, &QSlider::valueChanged, SpeedPlot_,
          &CSpeedPlot::adjustHorizontalScale);
}
} // namespace NSQt
} // namespace NSApplication
