#include <QObject>

#include <memory>

QT_BEGIN_NAMESPACE
class QMainWindow;
class QTextEdit;
class QGridLayout;
class QComboBox;
class QLabel;
class QWidget;
QT_END_NAMESPACE

namespace NSApplication {

namespace NSQt {
class CMainWindow;
}

namespace NSInterface {

class CTextModuleGUI {
  using CMainWindow = NSApplication::NSQt::CMainWindow;

public:
  CTextModuleGUI(CMainWindow*);
  ~CTextModuleGUI();

  QTextEdit* Text();
  QLabel* TextLabel();
  QComboBox* SelectionMenu();
  QLabel* SelectionMenuLabel();

  void setUpRegularCase();
  void setUpEmptyCase();

private:
  void setUpUI();

  void setUpWidgets();
  void setUpTextEdit();
  void setUpTextLabel();
  void setUpSelectionMenuLabel();
  void setUpSelectionMenu();
  void setUpLayout();
  void setUpWindow();
  void addWidgets();

  std::unique_ptr<QMainWindow> Window_;
  QWidget* CentralWidget_;
  QGridLayout* Layout_;
  QLabel* TextLabel_;
  QTextEdit* TextEdit_;

  QComboBox* SelectionMenu_;
  QLabel* SelectionMenuLabel_;

  int WindowWidth_;
  int WindowHeight_;
  int WindowWidthMin_;
  int WindowHeightMin_;
};

} // namespace NSInterface
} // namespace NSApplication
