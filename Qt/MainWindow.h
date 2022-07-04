#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "Interface/FileMenu.h"
#include "Interface/ModifiersMenu.h"
#include "Interface/TextModeView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QActionGroup;
class QButtonGroup;
class QCloseEvent;
class QSplitter;
class QTableView;
class QPlainTextEdit;
class QTreeView;
QT_END_NAMESPACE

class QwtPlot;

namespace NSApplication {
namespace NSQt {

class CMainWindow : public QMainWindow {
  Q_OBJECT
  using CTextModeInitData = NSInterface::CTextModeView::CInitData;
  using CModifiersModeInitData = NSInterface::CModifiersMenu::CInitData;

public:
  CMainWindow(QWidget* parent = nullptr);
  ~CMainWindow();

  void closeEvent(QCloseEvent* event);

  QTreeView* getSeanceView() const;
  CTextModeInitData getTextModeInitData() const;
  QButtonGroup* getTextButtonGroup() const;
  QButtonGroup* getShiftButtonGroup() const;
  QButtonGroup* getCtrlButtonGroup() const;
  QButtonGroup* getAltButtonGroup() const;
  QPlainTextEdit* getMainTextEdit() const;
  QwtPlot* getSpeedPlot() const;
  QTableView* getStatisticsTable() const;
  QwtPlot* getKeySchemePlot() const;
  QMenu* getFileMenu() const;
  CModifiersModeInitData getModifiersMenuInit() const;

Q_SIGNALS:
  bool closeMainWindow();

private:
  void adjustStaticInterface();
  void adjustMenu();
  void adjustMenu(QMenu* menu, std::unique_ptr<QActionGroup>* Group);
  void adjustSplitters();
  void adjustSplitter();
  void adjustSplitter2();
  void adjustSplitter3();
  void adjustMainSplitter();
  void adjustSplitter5();
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
  std::unique_ptr<QActionGroup> ShiftActions_;
  std::unique_ptr<QActionGroup> CtrlActions_;
  std::unique_ptr<QActionGroup> AltActions_;
};
} // namespace NSQt
} // namespace NSApplication

#endif // MAINWINDOW_H
