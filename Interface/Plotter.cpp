#include "Plotter.h"

#include <cassert>

#include <QwtLegend>
#include <QwtLegendLabel>
#include <QwtPlot>
#include <QwtPlotCurve>

namespace NSApplication {
namespace NSInterface {

namespace NSPlotterDetail {

CPlotterImpl::CPlotterImpl(QwtPlot* Plot)
    : Plot_(Plot), Speed0_(std::make_unique<QwtPlotCurve>("Speed")),
      Speed1_(std::make_unique<QwtPlotCurve>("Speed Derivative")),
      SpeedDataInput_(
          [this](const CPlotData& PlotData) { handlePlotData(PlotData); }) {
  assert(Plot_);
  adjustPlot();
}

NSPlotterDetail::CPlotterImpl::CPlotDataObserver*
NSPlotterDetail::CPlotterImpl::speedDataInput() {
  return &SpeedDataInput_;
}

CPlotterImpl::~CPlotterImpl() = default;

void CPlotterImpl::adjustPlot() {
  Plot_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  Speed0_->attach(Plot_);
  Speed0_->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
  Speed0_->setCurveAttribute(QwtPlotCurve::Fitted, true);
  Speed0_->setRenderHint(QwtPlotItem::RenderAntialiased);

  Speed0_->setPen(QColor(200, 50, 50));

  Speed1_->attach(Plot_);
  Speed1_->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
  Speed1_->setCurveAttribute(QwtPlotCurve::Fitted, true);
  Speed1_->setRenderHint(QwtPlotItem::RenderAntialiased);

  Speed1_->setPen(QColor(50, 50, 200));

  //  setZ(100); // on top of the marker
}

void NSPlotterDetail::CPlotterImpl::handlePlotData(const CPlotData& PlotData) {
  Speed0_->setRawSamples(PlotData.dataX(), PlotData.dataY0(),
                         PlotData.gridSize());
  Speed1_->setRawSamples(PlotData.dataX(), PlotData.dataY1(),
                         PlotData.gridSize());
  Plot_->replot();
}

} // namespace NSPlotterDetail
} // namespace NSInterface
} // namespace NSApplication
