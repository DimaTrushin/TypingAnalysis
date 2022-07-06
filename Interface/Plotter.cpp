#include "Plotter.h"

#include <cassert>

#include "qwt_legend.h"
#include "qwt_legend_label.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_grid.h"
#include <QSlider>

namespace NSApplication {
namespace NSInterface {

namespace NSPlotterDetail {

CSpeedPlotterImpl::CSpeedPlotterImpl(const CInitData& Data)
    : Plot_(Data.Plot), VerticalSlider_(Data.VerticalSlider),
      HorizontalSlider_(Data.HorizontalSlider),
      SpeedDataInput_(
          [this](CPlotDataCRef PlotData) { handlePlotData(PlotData); }),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }) {
  assert(Plot_);
  assert(VerticalSlider_);
  assert(HorizontalSlider_);
  adjustPlot();
  setCurves();
  adjustSliders();
  connectSliders();
}

CSpeedPlotterImpl::~CSpeedPlotterImpl() = default;

NSPlotterDetail::CSpeedPlotterImpl::CPlotDataObserver*
NSPlotterDetail::CSpeedPlotterImpl::speedDataInput() {
  return &SpeedDataInput_;
}

CSpeedPlotterImpl::CLocalizerObserver* CSpeedPlotterImpl::localizerInput() {
  return &LocalizerInput_;
}

void CSpeedPlotterImpl::legendChecked(const QVariant& itemInfo, bool on, int) {
  QwtPlotItem* plotItem = Plot_->infoToItem(itemInfo);
  if (plotItem)
    plotItem->setVisible(on);
  Plot_->replot();
}

void CSpeedPlotterImpl::adjustVerticalScale(int max) {
  if (max <= 0)
    return;
  Plot_->setAxisScale(QwtAxis::YLeft, 0, max * VerticalStep_);
  Plot_->replot();
}

void CSpeedPlotterImpl::adjustHorizontalScale(int max) {
  Plot_->setAxisScale(QwtAxis::XBottom, 0, max * HorizontalStep_);
  Plot_->replot();
}

void CSpeedPlotterImpl::adjustPlot() {
  Plot_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  Plot_->setTitle(title());
  std::unique_ptr<QwtLegend> Legend = std::make_unique<QwtLegend>();
  Legend->setDefaultItemMode(QwtLegendData::Checkable);
  QObject::connect(Legend.get(), &QwtLegend::checked, this,
                   &CSpeedPlotterImpl::legendChecked);
  Plot_->insertLegend(Legend.release(), QwtPlot::RightLegend);

  Plot_->setAxisScale(QwtAxis::YLeft, YLeftMinDefault_, YLeftMaxDefault_);
  Plot_->setAxisScale(QwtAxis::XBottom, XBottomMinDefault_, XBottomMaxDefault_);
  Plot_->setAxisVisible(QwtAxis::YRight);

  Plot_->setAxisTitle(QwtAxis::XBottom, horizontalAxisTitle());

  std::unique_ptr<QwtPlotGrid> grid = std::make_unique<QwtPlotGrid>();
  grid->enableXMin(true);
  grid->setMajorPen(Qt::gray, 0, Qt::DotLine);
  grid->setMinorPen(Qt::gray, 0, Qt::DotLine);
  grid.release()->attach(Plot_);
}

void CSpeedPlotterImpl::setCurves() {
  setCurve(density1Name(), QColor(200, 50, 50), true, &Speed0_);
  setCurve(derivative1Name(), QColor(50, 50, 200), false, &Speed1_);
  setCurve(density2Name(), QColor(50, 200, 50), false, &SpeedMB0_);
  setCurve(derivative2Name(), QColor(50, 50, 200), false, &SpeedMB1_);
  setCurve(density3Name(), QColor(50, 200, 200), false, &SpeedR0_);
  setCurve(derivative3Name(), QColor(50, 50, 200), false, &SpeedR1_);
}

void CSpeedPlotterImpl::setCurve(const QString& Name, QColor Color,
                                 bool Checked, QwtPlotCurve** Curve) {
  std::unique_ptr<QwtPlotCurve> SpeedCurve =
      std::make_unique<QwtPlotCurve>(Name);
  SpeedCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
  SpeedCurve->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
  SpeedCurve->setCurveAttribute(QwtPlotCurve::Fitted, true);
  SpeedCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
  SpeedCurve->setPen(Color);
  *Curve = SpeedCurve.release();
  (*Curve)->attach(Plot_);
  checkItem(*Curve, Checked);
}

void CSpeedPlotterImpl::checkItem(QwtPlotItem* item, bool on) {

  QwtLegend* lgd = qobject_cast<QwtLegend*>(Plot_->legend());

  QList<QWidget*> legendWidgets = lgd->legendWidgets(Plot_->itemToInfo(item));

  if (legendWidgets.size() == 1) {
    QwtLegendLabel* legendLabel =
        qobject_cast<QwtLegendLabel*>(legendWidgets[0]);

    if (legendLabel) {
      legendLabel->setChecked(on);
      legendLabel->checked(on);
    }
  }
}

void CSpeedPlotterImpl::adjustSliders() {
  VerticalSlider_->setRange(VerticalSliderMin_, VerticalSliderMax_);
  VerticalSlider_->setValue(VerticalSliderPosition_);
  HorizontalSlider_->setRange(HorizontalSliderMin_, HorizontalSliderMax_);
  HorizontalSlider_->setValue(HorizontalSliderPosition_);
}

void CSpeedPlotterImpl::connectSliders() {
  connect(VerticalSlider_, &QSlider::valueChanged, this,
          &CSpeedPlotterImpl::adjustVerticalScale);
  connect(HorizontalSlider_, &QSlider::valueChanged, this,
          &CSpeedPlotterImpl::adjustHorizontalScale);
}

void NSPlotterDetail::CSpeedPlotterImpl::handlePlotData(
    const CPlotData& PlotData) {
  Speed0_->setRawSamples(PlotData.dataX(), PlotData.dataY0(),
                         PlotData.gridSize());
  Speed1_->setRawSamples(PlotData.dataX(), PlotData.dataY1(),
                         PlotData.gridSize());
  SpeedMB0_->setRawSamples(PlotData.dataX(), PlotData.dataYMB0(),
                           PlotData.gridSize());
  SpeedMB1_->setRawSamples(PlotData.dataX(), PlotData.dataYMB1(),
                           PlotData.gridSize());
  SpeedR0_->setRawSamples(PlotData.dataX(), PlotData.dataYR0(),
                          PlotData.gridSize());
  SpeedR1_->setRawSamples(PlotData.dataX(), PlotData.dataYR1(),
                          PlotData.gridSize());
  Plot_->replot();
}

void CSpeedPlotterImpl::setLocale(const CLocalizer& Localizer) {
  Plot_->setTitle(Localizer.plotterTitle());
  Plot_->setAxisTitle(QwtAxis::XBottom, Localizer.horizontalAxisTitle());
  Speed0_->setTitle(Localizer.density1Name());
  Speed1_->setTitle(Localizer.derivative1Name());
  SpeedMB0_->setTitle(Localizer.density2Name());
  SpeedMB1_->setTitle(Localizer.derivative2Name());
  SpeedR0_->setTitle(Localizer.density3Name());
  SpeedR1_->setTitle(Localizer.derivative3Name());
}

QString CSpeedPlotterImpl::title() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().plotterTitle();
}

QString CSpeedPlotterImpl::horizontalAxisTitle() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().horizontalAxisTitle();
}

QString CSpeedPlotterImpl::density1Name() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().density1Name();
}

QString CSpeedPlotterImpl::derivative1Name() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().derivative1Name();
}

QString CSpeedPlotterImpl::density2Name() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().density2Name();
}

QString CSpeedPlotterImpl::derivative2Name() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().derivative2Name();
}

QString CSpeedPlotterImpl::density3Name() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().density3Name();
}

QString CSpeedPlotterImpl::derivative3Name() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().derivative3Name();
}

} // namespace NSPlotterDetail
} // namespace NSInterface
} // namespace NSApplication
