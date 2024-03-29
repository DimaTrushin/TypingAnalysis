#include "AnalyticalModule.h"

#include <algorithm>
#include <cassert>

#include "AppDebug/PerformanceLogger.h"
#include "ParallelModuleAccess.h"

namespace NSApplication {
namespace NSKernel {

CFunctionData::CFunctionData(CContainer&& Samples)
    : Samples_(std::move(Samples)) {
  PlotData_.fillPlots(Samples_);
}

void CFunctionData::set(CContainer&& Samples) {
  Samples_ = std::move(Samples);
  PlotData_.fillPlots(Samples_);
}

const CPlotData& CFunctionData::plotData() const {
  return PlotData_;
}

namespace NSAnalyticalModuleDetail {

CAnalyticalModuleImpl::CAnalyticalModuleImpl()
    : TextData_([this](const CTextData& Data) { handleTextData(Data); }) {
}

CAnalyticalModuleImpl::CTextDataObserver*
CAnalyticalModuleImpl::textDataInput() {
  return &TextData_;
}

void CAnalyticalModuleImpl::subscribeToSpeedData(CPlotDataObserver* obs) {
  assert(obs);
  DensityOut_.subscribe(obs);
}

void CAnalyticalModuleImpl::subscribeToAnalyticData(
    CAnalyticDataObserver* obs) {
  AnalyticDataOut_.subscribe(obs);
}

void CAnalyticalModuleImpl::handleTextData(const CTextData& Data) {
  NSAppDebug::CTimeAnchor Anchor("math & notify time =");

  auto FuncOpt = SpeedDataCacher_.find({&Data.rawSession(), Data.textInfo()});
  if (FuncOpt.has_value()) {
    DensityOut_.set(FuncOpt->get()->plotData());
    AnalyticDataOut_.set(
        CAnalyticData{std::cref(Data), std::cref(FuncOpt->get()->plotData())});
    return;
  }
  CTimer Timer;
  CContainer Samples = getSpeedData(Data);
  SpeedData_ = std::make_unique<CFunctionData>(std::move(Samples));
  CTime Elapsed = Timer.get();

  if (Elapsed > TimeLimit_) {
    auto SpeedData = SpeedDataCacher_.insert(
        {&Data.rawSession(), Data.textInfo()}, std::move(SpeedData_));
    assert(SpeedData != nullptr);
    DensityOut_.set(SpeedData->get()->plotData());
    AnalyticDataOut_.set(CAnalyticData{
        std::cref(Data), std::cref(SpeedData->get()->plotData())});
  } else {
    DensityOut_.set(SpeedData_->plotData());
    AnalyticDataOut_.set(
        CAnalyticData{std::cref(Data), std::cref(SpeedData_->plotData())});
  }
}

CAnalyticalModuleImpl::CContainer
CAnalyticalModuleImpl::getSpeedData(const CTextData& Data) const {
  CContainer SpeedData;
  switch (Data.textMode()) {
  case ETextMode::Raw:
    SpeedData = getSpeedDataS(Data.sessionSequencer());
    break;
  case ETextMode::Full:
    SpeedData = getSpeedDataS(Data.fullTextSequencer());
    break;
  case ETextMode::Printed:
    SpeedData = getSpeedDataS(Data.printedTextSequencer());
    break;
  default:
    assert(false);
  }
  return SpeedData;
}

template<class TSequencer>
CAnalyticalModuleImpl::CContainer
CAnalyticalModuleImpl::getSpeedDataS(TSequencer Sequencer) const {
  CContainer SpeedData;
  if (!Sequencer.isValid())
    return SpeedData;
  //  SpeedData.reserve(size()); // there is no way to compute size with
  //  a sequencer

  CTime PreviousTime = Sequencer.getPressingTime();
  for (; Sequencer.isValid(); Sequencer.next()) {
    if (!Sequencer.isAutoRepeat()) {
      CTime ResponseTime = Sequencer.getPressingTime() - PreviousTime;
      // Need filter here
      if (ResponseTime > CTime())
        SpeedData.push_back(1. / ResponseTime.toMinutesF());
      PreviousTime = Sequencer.getPressingTime();
    }
  }
  return SpeedData;
}

} // namespace NSAnalyticalModuleDetail
} // namespace NSKernel
} // namespace NSApplication
