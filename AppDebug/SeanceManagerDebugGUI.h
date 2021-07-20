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
class QHBoxLayout;
class QWidget;
class QTreeView;
QT_END_NAMESPACE

namespace NSAppDebug {

class CSeanceManagerDebugGUI {
  using CMainWindow = NSApplication::NSQt::CMainWindow;

public:
  CSeanceManagerDebugGUI(CMainWindow* MainWindow);
  ~CSeanceManagerDebugGUI();

  QTextEdit* Text();
  QTreeView* TreeView();

private:
  void setupUI();

  std::unique_ptr<QMainWindow> Window_;
  QWidget* CentralWidget_;
  QHBoxLayout* Layout_;
  QTextEdit* TextEdit_;
  QTreeView* TreeView_;
};

} // namespace NSAppDebug

#endif // NSAPPDEBUG_CSEANCEMANAGERDEBUGGUI_H
