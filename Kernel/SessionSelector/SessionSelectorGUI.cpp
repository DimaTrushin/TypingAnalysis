#include "SessionSelectorGUI.h"

#include "Qt/MainWindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

namespace NSApplication {
namespace NSInterface {

CSessionSelectorGUI::CSessionSelectorGUI(CMainWindow* MainWindow)
    : Window_(std::make_unique<QMainWindow>()),
      CentralWidget_(new QWidget(Window_.get())),
      Layout_(new QGridLayout(CentralWidget_)),
      TextEdit_(new QTextEdit(CentralWidget_)),
      SelectionMenuLabel_(new QLabel(CentralWidget_)),
      SelectionMenu_(new QSpinBox(CentralWidget_)),
      SelectButton_(new QPushButton(CentralWidget_)),
      ResetButton_(new QPushButton(CentralWidget_)),
      SpecialCasesMessage_(new QLabel(CentralWidget_)), WindowWidth_(700),
      WindowHeight_(700), WindowWidthMin_(600), WindowHeightMin_(200) {
  setUpUI();
}

CSessionSelectorGUI::~CSessionSelectorGUI() = default;

QTextEdit* CSessionSelectorGUI::Text() {
  return TextEdit_;
}

QSpinBox* CSessionSelectorGUI::SelectionMenu() {
  return SelectionMenu_;
}

QLabel* CSessionSelectorGUI::SelectionMenuLabel() {
  return SelectionMenuLabel_;
}

QPushButton* CSessionSelectorGUI::SelectButton() {
  return SelectButton_;
}

QPushButton* CSessionSelectorGUI::ResetButton() {
  return ResetButton_;
}

QLabel* CSessionSelectorGUI::SpecialCasesMessage() {
  return SpecialCasesMessage_;
}

void CSessionSelectorGUI::setUpUI() {
  setUpWidgets();
  setUpLayout();
  addWidgets();
  setUpWindow();
}

void CSessionSelectorGUI::setUpWidgets() {
  setUpTextEdit();
  setUpSelectionItems();
}

void CSessionSelectorGUI::setUpTextEdit() {
  TextEdit_->setFontFamily("Courier New");
  TextEdit_->setReadOnly(true);
}

void CSessionSelectorGUI::setUpSelectionItems() {
  SelectionMenu_->setAlignment(Qt::AlignHCenter);
  SelectButton_->setText("OK");
  ResetButton_->setText("Reset Session menu");
}

void CSessionSelectorGUI::setUpLayout() {
  Layout_->setRowStretch(4, 1);
}

void CSessionSelectorGUI::addWidgets() {
  Layout_->addWidget(SpecialCasesMessage_, 1, 1, 1, 4,
                     Qt::AlignHCenter | Qt::AlignTop);
  Layout_->addWidget(SelectionMenuLabel_, 2, 1, 1, 2);
  Layout_->addWidget(SelectionMenu_, 3, 1);
  Layout_->addWidget(SelectButton_, 3, 2);
  Layout_->addWidget(ResetButton_, 3, 3);
  Layout_->addWidget(TextEdit_, 4, 1, 1, 4);
}

void CSessionSelectorGUI::setUpWindow() {
  Window_->setWindowTitle("Seance menu");
  Window_->setCentralWidget(CentralWidget_);
  Window_->show();
}

void CSessionSelectorGUI::setUpRegularCase() {
  SelectionMenuLabel_->setAlignment(Qt::AlignHCenter);
  SelectionMenuLabel_->setText("Please select a session to proceed");
  Window_->resize(WindowWidth_, WindowHeight_);
  SpecialCasesMessage_->hide();
  TextEdit_->show();
  SelectionMenuLabel_->show();
  SelectionMenu_->show();
  SelectButton_->show();
  ResetButton_->show();
}

void CSessionSelectorGUI::setUpEmptyCase() {
  SpecialCasesMessage_->setText("There are no sessions in the current seance.");
  Window_->resize(WindowWidthMin_, WindowHeightMin_);
  SpecialCasesMessage_->show();
  TextEdit_->show();
  SelectionMenuLabel_->hide();
  SelectionMenu_->hide();
  SelectButton_->hide();
  ResetButton_->hide();
}

void CSessionSelectorGUI::setUpNoSeanceCase() {
  SpecialCasesMessage_->setText("No seance is uploaded so far.");
  Window_->resize(WindowWidthMin_, WindowHeightMin_);
  SpecialCasesMessage_->show();
  TextEdit_->hide();
  SelectionMenuLabel_->hide();
  SelectionMenu_->hide();
  SelectButton_->hide();
  ResetButton_->hide();
}

} // namespace NSInterface
} // namespace NSApplication
