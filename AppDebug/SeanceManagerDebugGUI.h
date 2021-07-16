#ifndef NSAPPDEBUG_CSEANCEMANAGERDEBUGGUI_H
#define NSAPPDEBUG_CSEANCEMANAGERDEBUGGUI_H

#include <QObject>

#include <memory>

namespace NSApplication {
namespace NSQt {
class CMainWindow;
}
} // namespace NSApplication

QT_BEGIN_NAMESPACE
class QMainWindow;
class QTextEdit;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace NSAppDebug {

class CSeanceManagerDebugGUI {
  using CMainWindow = NSApplication::NSQt::CMainWindow;

public:
  CSeanceManagerDebugGUI(CMainWindow* MainWindow);
  ~CSeanceManagerDebugGUI();

  QTextEdit* Text();

private:
  void setupUI();

  std::unique_ptr<QMainWindow> Window_;
  QWidget* CentralWidget_;
  QVBoxLayout* Layout_;
  QTextEdit* TextEdit_;
};

} // namespace NSAppDebug

#endif // NSAPPDEBUG_CSEANCEMANAGERDEBUGGUI_H
