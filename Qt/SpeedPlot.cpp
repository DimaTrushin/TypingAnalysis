#include "SpeedPlot.h"

namespace NSApplication {
namespace NSQt {

void CSpeedPlot::adjustVerticalScale(int max) {
  if (max <= 0)
    return;
  setAxisScale(QwtAxis::YLeft, 0, max * VerticalStep_);
  replot();
}

void CSpeedPlot::adjustHorizontalScale(int max) {
  setAxisScale(QwtAxis::XBottom, 0, max * HorizontalStep_);
  replot();
}

} // namespace NSQt
} // namespace NSApplication
