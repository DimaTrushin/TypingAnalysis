#ifndef NSAPPDEBUG_CKEYBOARDHANDLERDEBUGGUI_H
#define NSAPPDEBUG_CKEYBOARDHANDLERDEBUGGUI_H

#include <QObject>

#include <memory>


namespace NSApplication {
namespace NSQt {
class CMainWindow;
}
}

QT_BEGIN_NAMESPACE
class QMainWindow;
class QTextEdit;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace NSAppDebug {

class CKeyboardHandlerDebugGUI {
  using CMainWindow = NSApplication::NSQt::CMainWindow;
public:
  CKeyboardHandlerDebugGUI(CMainWindow* MainWindow);
  ~CKeyboardHandlerDebugGUI();
  QTextEdit* Text();
private:
  void setupUI();

  std::unique_ptr<QMainWindow> Window_;
  QWidget* CentralWidget_;
  QVBoxLayout* Layout_;
  QTextEdit* TextEdit_;
};

} // NSAppDebug

#endif // NSAPPDEBUG_CKEYBOARDHANDLERDEBUGGUI_H
