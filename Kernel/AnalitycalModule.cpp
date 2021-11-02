#include "AnalitycalModule.h"

#include <algorithm>
#include <cassert>

namespace NSApplication {
namespace NSKernel {

CPlotData::CPlotData()
    : X_(kDefaultGridSize), Y0_(kDefaultGridSize, 0.),
      Y1_(kDefaultGridSize, 0.) {
  fillXByDefault();
  assert(isCorrect_());
}

CPlotData::CIndex CPlotData::gridSize() const {
  assert(isCorrect_());
  return X_.size();
}

const CPlotData::Real* CPlotData::dataX() const {
  assert(isCorrect_());
  return X_.data();
}

const CPlotData::Real* CPlotData::dataY0() const {
  assert(isCorrect_());
  return Y0_.data();
}

const CPlotData::Real* CPlotData::dataY1() const {
  assert(isCorrect_());
  return Y1_.data();
}

void CPlotData::fillXByDefault() {
  Real step = (Maximum_ - Minimum_) / (kDefaultGridSize - 1);
  for (size_t i = 0; i < kDefaultGridSize; ++i) {
    X_[i] = Minimum_ + step * i;
  }
}

bool CPlotData::isCorrect_() const {
  return X_.size() == Y0_.size() && X_.size() == Y1_.size();
}

} // namespace NSKernel
} // namespace NSApplication
