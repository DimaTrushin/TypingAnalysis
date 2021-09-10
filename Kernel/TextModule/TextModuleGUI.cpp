#include "TextModuleGUI.h"

#include "Qt/MainWindow.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QTextEdit>

namespace NSApplication {
namespace NSInterface {

CTextModuleGUI::CTextModuleGUI(CMainWindow* MainWindow)
    : Window_(std::make_unique<QMainWindow>()),
      CentralWidget_(new QWidget(Window_.get())),
      Layout_(new QGridLayout(CentralWidget_)),
      TextLabel_(new QLabel(CentralWidget_)),
      TextEdit_(new QTextEdit(CentralWidget_)),
      SelectionMenuLabel_(new QLabel(CentralWidget_)),
      SelectionMenu_(new QComboBox(CentralWidget_)), WindowWidth_(700),
      WindowHeight_(600), WindowWidthMin_(600), WindowHeightMin_(200) {
  setUpUI();
  Window_->show();
}

CTextModuleGUI::~CTextModuleGUI() = default;

QLabel* CTextModuleGUI::TextLabel() {
  return TextLabel_;
}

QTextEdit* CTextModuleGUI::Text() {
  return TextEdit_;
}

QComboBox* CTextModuleGUI::SelectionMenu() {
  return SelectionMenu_;
}

QLabel* CTextModuleGUI::SelectionMenuLabel() {
  return SelectionMenuLabel_;
}

void CTextModuleGUI::setUpRegularCase() {
  TextLabel()->setAlignment(Qt::AlignLeft);
  Window_->resize(WindowWidth_, WindowHeight_);
  TextLabel()->setText("Description of the selected session");
  TextEdit_->show();
}

void CTextModuleGUI::setUpEmptyCase() {
  TextLabel_->setAlignment(Qt::AlignLeft);
  TextLabel_->setText("No session is selected.");
  Window_->resize(WindowWidthMin_, WindowHeightMin_);
  TextEdit_->hide();
  SelectionMenu_->setCurrentIndex(0);
}

void CTextModuleGUI::setUpUI() {
  setUpWidgets();
  setUpEmptyCase();
  setUpLayout();
  addWidgets();
  setUpWindow();
}

void CTextModuleGUI::setUpWidgets() {
  setUpTextEdit();
  setUpSelectionMenuLabel();
  setUpSelectionMenu();
}

void CTextModuleGUI::setUpTextEdit() {
  TextEdit_->setFontFamily("Courier New");
  TextEdit_->setReadOnly(true);
}

void CTextModuleGUI::setUpSelectionMenuLabel() {
  SelectionMenuLabel_->setAlignment(Qt::AlignHCenter);
  SelectionMenuLabel_->setText("Please select a text mode");
}

void CTextModuleGUI::setUpSelectionMenu() {
  SelectionMenu_->addItems({"Raw", "Full", "Printed"});
  SelectionMenu_->setCurrentIndex(0);
}

void CTextModuleGUI::setUpLayout() {
  Layout_->setColumnStretch(2, 1);
  Layout_->setRowStretch(3, 1);
}

void CTextModuleGUI::addWidgets() {
  Layout_->addWidget(SelectionMenuLabel_, 2, 1);
  Layout_->addWidget(SelectionMenu_, 3, 1, Qt::AlignTop);
  Layout_->addWidget(TextLabel_, 1, 2, 1, 2, Qt::AlignHCenter);
  Layout_->addWidget(TextEdit_, 2, 2, 2, 2);
}

void CTextModuleGUI::setUpWindow() {
  Window_->setWindowTitle("Session menu");
  Window_->setCentralWidget(CentralWidget_);
}

} // namespace NSInterface
} // namespace NSApplication
