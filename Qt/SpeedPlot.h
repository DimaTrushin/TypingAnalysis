#ifndef NSAPPLICATION_NSQT_CSPEEDPLOT_H
#define NSAPPLICATION_NSQT_CSPEEDPLOT_H

#include "qwt_plot.h"

namespace NSApplication {
namespace NSQt {

class CSpeedPlot : public QwtPlot {
  Q_OBJECT
  using CBase = QwtPlot;
  using CBase::CBase;

public:
public Q_SLOTS:
  void adjustVerticalScale(int max);
  void adjustHorizontalScale(int max);

private:
  double VerticalStep_ = 0.0001;
  double HorizontalStep_ = 25;
};

} // namespace NSQt
} // namespace NSApplication

#endif // NSAPPLICATION_NSQT_CSPEEDPLOT_H
