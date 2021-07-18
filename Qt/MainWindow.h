#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QCloseEvent;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSQt {

class CMainWindow : public QMainWindow {
  Q_OBJECT
public:
  CMainWindow(QWidget* parent = nullptr);
  ~CMainWindow();

  void closeEvent(QCloseEvent* event);

signals:
  bool closeMainWindow();

private:
  std::unique_ptr<Ui::MainWindow> ui_;
};
} // namespace NSQt
} // namespace NSApplication

#endif // MAINWINDOW_H
