#ifndef NSAPPLICATION_NSKERNEL_CPLOTDATA_H
#define NSAPPLICATION_NSKERNEL_CPLOTDATA_H

#include "MathFunction.h"

#include <vector>

namespace NSApplication {
namespace NSKernel {

class CPlotData {
  using CContainer = std::vector<double>;

public:
  using CIndex = int64_t;

  CPlotData();
  CPlotData(CIndex GridSize);

  CIndex gridSize() const;

  const double* dataX() const;
  const double* dataY0() const;
  const double* dataY1() const;
  const double* dataYMB0() const;
  const double* dataYMB1() const;

  void fillY0(const CContainer& Samples, const CNormalApproximation0& F);
  void fillY1(const CContainer& Samples, const CNormalApproximation1& F);
  void fillYMB0(const CContainer& Samples,
                const CMaxwellBoltzmannApproximation0& F);
  void fillYMB1(const CContainer& Samples,
                const CMaxwellBoltzmannApproximation1& F);

private:
  static constexpr const CIndex kDefaultGridSize = 2500;
  static constexpr const double kMaximum = 2500.;
  static constexpr const double kMinimum = 1.;

  void fillX();

  bool isCorrect_() const;

  CContainer X_;
  CContainer Y0_;
  CContainer Y1_;
  CContainer YMB0_;
  CContainer YMB1_;
  double Maximum_ = kMaximum;
  double Minimum_ = kMinimum;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CPLOTDATA_H
