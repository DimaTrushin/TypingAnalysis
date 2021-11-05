#include "AnalyticalModule.h"

#include <algorithm>
#include <cassert>

#include "ParallelModuleAccess.h"

#include "TimerAccess.h"
#include <QDebug>

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
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X_.size(), [&](size_t i) {
    Y0_[i] = F(Samples, X_[i]);
    ;
  });
}

void CPlotData::fillY1(const CContainer& Samples, const CDensity1& F) {
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

void CFunctionData::set(CContainer&& Samples) {
  Samples_ = std::move(Samples);
  PlotData_.fillY0(Samples_, Density0_);
  PlotData_.fillY1(Samples_, Density1_);
}

const CPlotData& CFunctionData::plotData() const {
  return PlotData_;
}

namespace NSAnalyticalModuleDetail {
CAnalyticalModuleImpl::CAnalyticalModuleImpl()
    : TextData_([this](const CTextData& Data) { handleTextData(Data); }),
      DensityOut_([this]() -> CPlotDataGetType {
        return std::cref(SpeedData_.plotData());
      }) {
}

CAnalyticalModuleImpl::CTextDataObserver*
CAnalyticalModuleImpl::textDataInput() {
  return &TextData_;
}

void CAnalyticalModuleImpl::subscribeToSpeedData(CPlotDataObserver* obs) {
  assert(obs);
  DensityOut_.subscribe(obs);
}

void CAnalyticalModuleImpl::handleTextData(const CTextData& Data) {
  CTime time = CTimerAccess()->get();
  // preliminary implementation
  CContainer Samples = getSpeedData(Data);
  SpeedData_.set(std::move(Samples));
  DensityOut_.notify();
  time = CTimerAccess()->get() - time;
  qDebug() << "math time =" << time.toMicroSecondsI() << "mc";
}

CAnalyticalModuleImpl::CContainer
CAnalyticalModuleImpl::getSpeedData(const CTextData& Data) const {
  CContainer SpeedData;
  switch (Data.TextMode.TextMode) {
  case ETextMode::Raw:
    SpeedData = getRawSpeedData(Data.Session);
    break;
  case ETextMode::Full:
    SpeedData = getFullTextSpeedData(Data.TextTree);
    break;
  case ETextMode::Printed:
    SpeedData = getTextSpeedData(Data.TextTree);
    break;
  default:
    assert(false);
  }
  return SpeedData;
}

CAnalyticalModuleImpl::CContainer
CAnalyticalModuleImpl::getRawSpeedData(const CSession& Session) const {
  CContainer SpeedData;
  if (Session.empty())
    return SpeedData;
  // TO DO
  // debug version
  SpeedData.reserve(Session.size());
  auto iter = Session.begin();
  CTime PreviousTime = iter->getPressingTime();
  for (; iter != Session.end(); ++iter) {
    CTime ResponseTime = iter->getPressingTime() - PreviousTime;
    if (ResponseTime > CTime())
      SpeedData.push_back(1. / ResponseTime.toSecondsF());
    PreviousTime = iter->getPressingTime();
  }
  return SpeedData;
}

CAnalyticalModuleImpl::CContainer CAnalyticalModuleImpl::getFullTextSpeedData(
    const CTextDataTree& TextTree) const {
  CContainer SpeedData;
  // TO DO
  // debug version
  if (TextTree->getFullTextLength() == 0)
    return SpeedData;
  SpeedData.reserve(TextTree->getFullTextLength());
  auto iter = TextTree->beginFullText();
  CTime PreviousTime = iter->getPressingTime();
  for (; iter != TextTree->endFullText(); ++iter) {
    CTime ResponseTime = iter->getPressingTime() - PreviousTime;
    if (ResponseTime > CTime())
      SpeedData.push_back(1. / ResponseTime.toSecondsF());
    PreviousTime = iter->getPressingTime();
  }
  return SpeedData;
}

CAnalyticalModuleImpl::CContainer
CAnalyticalModuleImpl::getTextSpeedData(const CTextDataTree& TextTree) const {
  CContainer SpeedData;
  // TO DO
  // debug version
  if (TextTree->getPrintedTextLength() == 0)
    return SpeedData;
  SpeedData.reserve(TextTree->getPrintedTextLength());
  auto iter = TextTree->beginPrintedText();
  CTime PreviousTime = iter->getPressingTime();
  for (; iter != TextTree->endPrintedText(); ++iter) {
    CTime ResponseTime = iter->getPressingTime() - PreviousTime;
    if (ResponseTime > CTime())
      SpeedData.push_back(1. / ResponseTime.toSecondsF());
    PreviousTime = iter->getPressingTime();
  }
  return SpeedData;
}
} // namespace NSAnalyticalModuleDetail
} // namespace NSKernel
} // namespace NSApplication
