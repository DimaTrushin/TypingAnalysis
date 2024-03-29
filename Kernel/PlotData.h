#ifndef NSAPPLICATION_NSKERNEL_CPLOTDATA_H
#define NSAPPLICATION_NSKERNEL_CPLOTDATA_H

#include <cstdint>
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
  const double* dataYR0() const;
  const double* dataYR1() const;

  struct CPointData {
    double x;
    double y;
  };

  CPointData max0() const;
  int score() const;

  void fillPlots(const CContainer& Samples);

private:
  static constexpr const CIndex kDefaultGridSize = 2501;
  static constexpr const double kMaximum = 2500.;
  static constexpr const double kMinimum = 0.;

  void fillX();
  void find_max0();
  void find_score_();

  bool isCorrect_() const;

  CContainer X_;
  CContainer Y0_;
  CContainer Y1_;
  CContainer YMB0_;
  CContainer YMB1_;
  CContainer YR0_;
  CContainer YR1_;
  double Maximum_ = kMaximum;
  double Minimum_ = kMinimum;
  size_t index_max0_ = 0;
  double Score_ = 0.;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CPLOTDATA_H
