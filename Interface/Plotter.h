#ifndef NSAPPLICATION_NSINTERFACE_CPLOTTER_H
#define NSAPPLICATION_NSINTERFACE_CPLOTTER_H

#include <QObject>

#include <memory>

#include "Kernel/PlotData.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/Localizer.h"

class QwtPlot;
class QwtPlotCurve;
class QwtPlotItem;

namespace NSApplication {
namespace NSInterface {

namespace NSPlotterDetail {

class CSpeedPlotterImpl : public QObject {
  Q_OBJECT

  using CPlotData = NSKernel::CPlotData;
  using CPlotDataObserver = NSLibrary::CObserver<CPlotData>;
  using CPlotDataInput = NSLibrary::CHotInput<CPlotData>;

  using CLocalizer = NSLocal::CSpeedPlotterLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

public:
  CSpeedPlotterImpl(QwtPlot*);
  ~CSpeedPlotterImpl();

  CPlotDataObserver* speedDataInput();
  CLocalizerObserver* localizerInput();

public Q_SLOTS:
  void legendChecked(const QVariant&, bool, int);

private:
  void adjustPlot();
  void setCurves();
  void checkItem(QwtPlotItem* item, bool on);

  void handlePlotData(const CPlotData& PlotData);

  void setLocale(const CLocalizer& Localizer);

  QString title() const;
  QString horizontalAxisTitle() const;
  QString density1Name() const;
  QString derivative1Name() const;
  QString density2Name() const;
  QString derivative2Name() const;
  QString density3Name() const;
  QString derivative3Name() const;

  QwtPlot* Plot_;
  QwtPlotCurve* Speed0_;
  QwtPlotCurve* Speed1_;
  QwtPlotCurve* SpeedMB0_;
  QwtPlotCurve* SpeedMB1_;
  QwtPlotCurve* SpeedR0_;
  QwtPlotCurve* SpeedR1_;
  CPlotDataInput SpeedDataInput_;
  CLocalizerInput LocalizerInput_;
};

} // namespace NSPlotterDetail

using CSpeedPlotter =
    NSLibrary::CViewWrapper<NSPlotterDetail::CSpeedPlotterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CPLOTTER_H
