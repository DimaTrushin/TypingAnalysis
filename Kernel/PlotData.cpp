#include "PlotData.h"

#include "ParallelModuleAccess.h"

#include <cassert>

namespace NSApplication {
namespace NSKernel {

CPlotData::CPlotData()
    : X_(kDefaultGridSize), Y0_(kDefaultGridSize, 0.),
      Y1_(kDefaultGridSize, 0.) {
  fillX();
  assert(isCorrect_());
}

CPlotData::CPlotData(CIndex GridSize)
    : X_(GridSize), Y0_(GridSize, 0.), Y1_(GridSize, 0.) {
  fillX();
  assert(isCorrect_());
}

CPlotData::CIndex CPlotData::gridSize() const {
  assert(isCorrect_());
  return X_.size();
}

const double* CPlotData::dataX() const {
  assert(isCorrect_());
  return X_.data();
}

const double* CPlotData::dataY0() const {
  assert(isCorrect_());
  return Y0_.data();
}

const double* CPlotData::dataY1() const {
  assert(isCorrect_());
  return Y1_.data();
}

void CPlotData::fillY0(const CContainer& Samples,
                       const CNormalApproximation0& F) {
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X_.size(), [&](size_t i) {
    Y0_[i] = F(Samples, X_[i]);
    ;
  });
}

void CPlotData::fillY1(const CContainer& Samples,
                       const CNormalApproximation1& F) {
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X_.size(), [&](size_t i) {
    Y1_[i] = F(Samples, X_[i]);
    ;
  });
}

void CPlotData::fillX() {
  double step = (Maximum_ - Minimum_) / (X_.size() - 1);
  for (size_t i = 0; i < X_.size(); ++i) {
    X_[i] = Minimum_ + step * i;
  }
}

bool CPlotData::isCorrect_() const {
  return X_.size() == Y0_.size() && X_.size() == Y1_.size();
}

} // namespace NSKernel
} // namespace NSApplication
