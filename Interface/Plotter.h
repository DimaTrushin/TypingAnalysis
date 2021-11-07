#ifndef NSAPPLICATION_NSINTERFACE_CPLOTTER_H
#define NSAPPLICATION_NSINTERFACE_CPLOTTER_H

#include <QObject>

#include <memory>

#include "Kernel/PlotData.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

class QwtPlot;
class QwtPlotCurve;
class QwtPlotItem;

namespace NSApplication {
namespace NSInterface {

namespace NSPlotterDetail {

class CPlotterImpl : public QObject {
  Q_OBJECT

  using CPlotData = NSKernel::CPlotData;
  using CPlotDataObserver = NSLibrary::CObserver<CPlotData>;
  using CPlotDataInput = NSLibrary::CHotInput<CPlotData>;

public:
  CPlotterImpl(QwtPlot*);
  ~CPlotterImpl();

  CPlotDataObserver* speedDataInput();

public slots:
  void legendChecked(const QVariant&, bool, int);

private:
  void adjustPlot();
  void setCurves();
  void checkItem(QwtPlotItem* item, bool on);

  void handlePlotData(const CPlotData& PlotData);

  QwtPlot* Plot_;
  QwtPlotCurve* Speed0_;
  QwtPlotCurve* Speed1_;
  CPlotDataInput SpeedDataInput_;
};

} // namespace NSPlotterDetail

using CPlotter = NSLibrary::CViewWrapper<NSPlotterDetail::CPlotterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CPLOTTER_H
