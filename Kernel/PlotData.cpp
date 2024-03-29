#include "PlotData.h"

#ifdef _MSC_VER
#pragma warning(disable : 4324)
#pragma warning(disable : 4515)
#endif
#include "MathModuleAccess.h"
#ifdef _MSC_VER
#pragma warning(default : 4324)
#pragma warning(default : 4515)
#endif

#include <cassert>

namespace NSApplication {
namespace NSKernel {

CPlotData::CPlotData()
    : X_(kDefaultGridSize), Y0_(kDefaultGridSize, 0.),
      Y1_(kDefaultGridSize, 0.), YMB0_(kDefaultGridSize, 0.),
      YMB1_(kDefaultGridSize, 0.), YR0_(kDefaultGridSize, 0.),
      YR1_(kDefaultGridSize, 0.) {
  fillX();
  assert(isCorrect_());
}

CPlotData::CPlotData(CIndex GridSize)
    : X_(GridSize), Y0_(GridSize, 0.), Y1_(GridSize, 0.), YMB0_(GridSize, 0.),
      YMB1_(GridSize, 0.), YR0_(GridSize, 0.), YR1_(GridSize, 0.) {
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

const double* CPlotData::dataYMB0() const {
  assert(isCorrect_());
  return YMB0_.data();
}

const double* CPlotData::dataYMB1() const {
  assert(isCorrect_());
  return YMB1_.data();
}

const double* CPlotData::dataYR0() const {
  assert(isCorrect_());
  return YR0_.data();
}

const double* CPlotData::dataYR1() const {
  assert(isCorrect_());
  return YR1_.data();
}

CPlotData::CPointData CPlotData::max0() const {
  return {X_[index_max0_], Y0_[index_max0_]};
}

int CPlotData::score() const {
  return static_cast<int>(Score_ * 100.);
}

void CPlotData::fillPlots(const CContainer& Samples) {
  CMathAccess Math;
  Math->fillPlots(Samples, X_, &Y0_, &Y1_, &YMB0_, &YMB1_, &YR0_, &YR1_);
  find_max0();
  find_score_();
}

void CPlotData::fillX() {
  double step = (Maximum_ - Minimum_) / (X_.size() - 1);
  for (size_t i = 0; i < X_.size(); ++i) {
    X_[i] = Minimum_ + step * i;
  }
}

void CPlotData::find_max0() {
  double max0 = Y0_[0];
  index_max0_ = 0;
  for (size_t i = 1; i < X_.size(); ++i) {
    if (Y0_[i] > max0) {
      max0 = Y0_[i];
      index_max0_ = i;
    }
  }
}

void CPlotData::find_score_() {
  Score_ = Y0_[index_max0_] / NSCompute::CFunctions::CNormal<0>::compute(
                                  X_[index_max0_], X_[index_max0_]);
}

bool CPlotData::isCorrect_() const {
  return X_.size() == Y0_.size() && X_.size() == Y1_.size();
}

} // namespace NSKernel
} // namespace NSApplication
