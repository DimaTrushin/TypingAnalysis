#include "AnalitycalModule.h"

#include <algorithm>
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

void CPlotData::fillY0(const CContainer& Samples, const CDensity0& F) {
  // Need to parallelize
  for (size_t i = 0; i < X_.size(); ++i) {
    Y0_[i] = F(Samples, X_[i]);
  }
}

void CPlotData::fillY1(const CContainer& Samples, const CDensity1& F) {
  // Need to parallelize
  for (size_t i = 0; i < X_.size(); ++i) {
    Y1_[i] = F(Samples, X_[i]);
  }
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

void CFunctionData::set(CContainer&& Samples) {
  Samples_ = std::move(Samples);
  PlotData_.fillY0(Samples_, Density0_);
  PlotData_.fillY1(Samples_, Density1_);
}

const CPlotData& CFunctionData::plotData() const {
  return PlotData_;
}

namespace NSAnalitycalModuleDetail {
CAnalitycalModuleImpl::CAnalitycalModuleImpl()
    : TextData_([this](const CTextData& Data) { handleTextData(Data); }),
      DensityOut_([this]() -> CPlotDataGetType {
        return std::cref(SpeedData_.plotData());
      }) {
}

void CAnalitycalModuleImpl::handleTextData(const CTextData& Data) {
  // preliminary implementation
  CContainer Samples = getSpeedData(Data);
  SpeedData_.set(std::move(Samples));
  DensityOut_.notify();
}

CAnalitycalModuleImpl::CContainer
CAnalitycalModuleImpl::getSpeedData(const CTextData& Data) const {
  // TO DO
  return CContainer();
}
} // namespace NSAnalitycalModuleDetail
} // namespace NSKernel
} // namespace NSApplication
