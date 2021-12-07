#include "KeySchemePlotter.h"

#include "qwt_plot.h"
#include "qwt_plot_grid.h"
#include "qwt_scale_draw.h"
#include "qwt_text.h"

#include <QDebug>

#include <cassert>

namespace NSApplication {
namespace NSInterface {

namespace NSKeySchemePlotterDetail {

namespace {

class LabelScaleDraw : public QwtScaleDraw {
  QwtText label(double value) const override {
    switch (int(value)) {
    case 0:
      return QString("Thumb");
    case 1:
      return QString("Left Pinky");
    case 2:
      return QString("Left Ring");
    case 3:
      return QString("Left Middle");
    case 4:
      return QString("Left Index");
    case 5:
      return QString("Right Index");
    case 6:
      return QString("Right Middle");
    case 7:
      return QString("Right Ring");
    case 8:
      return QString("Right Pinky");
    case 9:
      return QString("Unassigned");
    default:
      break;
    }
    return QwtScaleDraw::label(value);
  }
};
} // namespace

CKeySchemePlotterImpl::CKeySchemePlotterImpl(QwtPlot* Plot) : Plot_(Plot) {
  assert(Plot_);

  Plot_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  Plot_->setTitle("Key Scheme");

  Plot_->setMinimumHeight(300);

  Plot_->setAxisScaleDraw(QwtAxis::YLeft, new LabelScaleDraw());

  Plot_->setAxisTitle(QwtAxis::XBottom, "Time, ms");
  Plot_->setAxisScale(QwtAxis::YLeft, -0.5, 9.5, 1.0);
  Plot_->setAxisMaxMajor(QwtAxis::YLeft, 10);
  Plot_->setAxisMaxMinor(QwtAxis::YLeft, 3);

  Plot_->setAxisTitle(QwtAxis::YLeft, "Fingers");

  std::unique_ptr<QwtPlotGrid> grid = std::make_unique<QwtPlotGrid>();
  grid->enableX(false);
  grid->enableYMin(true);
  grid->setMajorPen(Qt::gray, 0, Qt::NoPen);
  grid->setMinorPen(Qt::gray, 0, Qt::SolidLine);
  grid.release()->attach(Plot_);
}
} // namespace NSKeySchemePlotterDetail
} // namespace NSInterface
} // namespace NSApplication
