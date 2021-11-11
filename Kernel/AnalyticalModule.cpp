#include "AnalyticalModule.h"

#include <algorithm>
#include <cassert>

#include "ParallelModuleAccess.h"

#include "TimerAccess.h"
#include <QDebug>

namespace NSApplication {
namespace NSKernel {

void CFunctionData::set(CContainer&& Samples) {
  Samples_ = std::move(Samples);
  PlotData_.fillY0(Samples_, Density0_);
  PlotData_.fillY1(Samples_, Density1_);
  PlotData_.fillYMB0(Samples_, DensityMB0_);
  PlotData_.fillYMB1(Samples_, DensityMB1_);
  PlotData_.fillYR0(Samples_, DensityR0_);
  PlotData_.fillYR1(Samples_, DensityR1_);
}

const CPlotData& CFunctionData::plotData() const {
  return PlotData_;
}

double CFunctionData::compute0(double arg) const {
  return Density0_(Samples_, arg);
}

double CFunctionData::compute1(double arg) const {
  return Density1_(Samples_, arg);
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
  // TO DO
  // Need to exclude auto repeat
  CContainer SpeedData;
  switch (Data.TextMode.TextMode) {
  case ETextMode::Raw:
    SpeedData = getSpeedData(Data.rawSession());
    break;
  case ETextMode::Full:
    SpeedData = getSpeedData(Data.textConstFullView());
    break;
  case ETextMode::Printed:
    SpeedData = getSpeedData(Data.textConstPrintedView());
    break;
  default:
    assert(false);
  }
  return SpeedData;
}

template<class TText>
CAnalyticalModuleImpl::CContainer
CAnalyticalModuleImpl::getSpeedData(const TText& TextView) const {
  // TO DO
  // Need to exclude auto repeat
  CContainer SpeedData;
  if (TextView.empty())
    return SpeedData;
  SpeedData.reserve(TextView.size());
  auto iter = TextView.begin();
  CTime PreviousTime = iter->getPressingTime();
  for (; iter != TextView.end(); ++iter) {
    CTime ResponseTime = iter->getPressingTime() - PreviousTime;
    // Need filter here
    if (ResponseTime > CTime())
      SpeedData.push_back(60. / ResponseTime.toSecondsF());
    PreviousTime = iter->getPressingTime();
  }
  return SpeedData;
}

} // namespace NSAnalyticalModuleDetail
} // namespace NSKernel
} // namespace NSApplication
