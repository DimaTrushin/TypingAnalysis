#include <QObject>

#include <memory>

QT_BEGIN_NAMESPACE
class QMainWindow;
class QTextEdit;
class QGridLayout;
class QWidget;
class QLabel;
class QSpinBox;
class QPushButton;
QT_END_NAMESPACE

namespace NSApplication {

namespace NSQt {
class CMainWindow;
}

namespace NSInterface {
class CSessionSelectorGUI {
  using CMainWindow = NSApplication::NSQt::CMainWindow;

public:
  CSessionSelectorGUI(CMainWindow*);
  ~CSessionSelectorGUI();

  QTextEdit* Text();
  QSpinBox* SelectionMenu();
  QLabel* SelectionMenuLabel();
  QPushButton* SelectButton();
  QPushButton* ResetButton();
  QLabel* SpecialCasesMessage();

  void setUpRegularCase();
  void setUpEmptyCase();
  void setUpNoSeanceCase();

private:
  void setUpUI();
  void setUpWidgets();
  void setUpTextEdit();
  void setUpSelectionItems();
  void setUpLayout();
  void addWidgets();
  void setUpWindow();

  std::unique_ptr<QMainWindow> Window_;
  QWidget* CentralWidget_;
  QGridLayout* Layout_;
  QTextEdit* TextEdit_;
  QSpinBox* SelectionMenu_;
  QLabel* SelectionMenuLabel_;
  QPushButton* SelectButton_;
  QPushButton* ResetButton_;
  QLabel* SpecialCasesMessage_;

  int WindowWidth_;
  int WindowHeight_;
  int WindowWidthMin_;
  int WindowHeightMin_;
};

} // namespace NSInterface
} // namespace NSApplication
