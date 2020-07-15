#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

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
};
} // NSQt
} // NSApplication

#endif // MAINWINDOW_H
