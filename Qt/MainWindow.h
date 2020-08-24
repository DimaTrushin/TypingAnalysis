#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>

#ifdef KEYBOARD_HANDLER_DEBUG
#include "AppDebug/KeyboardHandlerOut.h"
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace NSApplication {
namespace NSQt {

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
private:
  std::unique_ptr<Ui::MainWindow> ui_;
#ifdef KEYBOARD_HANDLER_DEBUG
  std::unique_ptr<NSAppDebug::CKeyboardHandlerOut> KeyboardHandlerOut_;
#endif
};
} // NSQt
} // NSApplication

#endif // MAINWINDOW_H
