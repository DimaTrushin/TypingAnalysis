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

private:
  void adjustPlot();

  void handlePlotData(const CPlotData& PlotData);

  QwtPlot* Plot_;
  // Probably I should use raw pointers and qt will manage the memory
  std::unique_ptr<QwtPlotCurve> Speed0_;
  std::unique_ptr<QwtPlotCurve> Speed1_;
  CPlotDataInput SpeedDataInput_;
};

} // namespace NSPlotterDetail

using CPlotter = NSLibrary::CViewWrapper<NSPlotterDetail::CPlotterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CPLOTTER_H
