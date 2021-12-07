#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QButtonGroup;
class QCloseEvent;
class QSplitter;
class QTableView;
class QTextEdit;
class QTreeView;
QT_END_NAMESPACE

class QwtPlot;

namespace NSApplication {
namespace NSQt {

class CMainWindow : public QMainWindow {
  Q_OBJECT
public:
  CMainWindow(QWidget* parent = nullptr);
  ~CMainWindow();

  void closeEvent(QCloseEvent* event);

  QTreeView* getSeanceView() const;
  QButtonGroup* getTextButtonGroup() const;
  QButtonGroup* getShiftButtonGroup() const;
  QButtonGroup* getCtrlButtonGroup() const;
  QButtonGroup* getAltButtonGroup() const;
  QTextEdit* getMainTextEdit() const;
  QwtPlot* getSpeedPlot() const;
  QTableView* getStatisticsTable() const;
  QwtPlot* getKeySchemePlot() const;

Q_SIGNALS:
  bool closeMainWindow();

private:
  void adjustStaticInterface();
  void adjustSplitters();
  void adjustSplitter();
  void adjustSplitter2();
  void adjustSplitter3();
  void adjustMainSplitter();
  void adjustSplitter5();
  void adjustSplitter6();
  void adjustButtonGroups();
  void adjustButtonGroup();
  void adjustButtonGroup2();
  void adjustButtonGroup3();
  void adjustButtonGroup4();

  void addQwtPlotPanel();
  void addQwtKeyScheme();

  std::unique_ptr<Ui::MainWindow> ui_;
  QwtPlot* SpeedPlot_;
  QwtPlot* KeySchemePlot_;
};
} // namespace NSQt
} // namespace NSApplication

#endif // MAINWINDOW_H
