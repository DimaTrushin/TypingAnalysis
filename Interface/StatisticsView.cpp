#include "StatisticsView.h"

#include "AppDebug/PerformanceLogger.h"
#include "TimerAccess.h"

#include <QTableView>

#include <cassert>

namespace NSApplication {
namespace NSInterface {

namespace NSStatisticsViewDetail {

CStatisticsViewImpl::CStatisticsViewImpl(QTableView* TableView)
    : TableView_(TableView),
      ViewLocalizerInput_(
          [this](const CLocalizer& Localizer) { setViewLocale(Localizer); }),
      StatisticsInput_([this](const CStatisticsDescription& Statistics) {
        handleStatistics(Statistics);
      }) {
  assert(TableView_);
  TableView_->setModel(this);
}

CStatisticsViewImpl::CLocalizerObserver* CStatisticsViewImpl::localizerInput() {
  return &ViewLocalizerInput_;
}

CStatisticsViewImpl::CStatisticsObserver*
CStatisticsViewImpl::statisticsDescriptionInput() {
  return &StatisticsInput_;
}

void CStatisticsViewImpl::handleStatistics(
    const CStatisticsDescription& Statistics) {
  printStatistics(Statistics);
}

void CStatisticsViewImpl::setViewLocale(const CLocalizer& Localizer) {
  setLocale(Localizer);
  if (StatisticsInput_.hasData())
    handleStatistics(StatisticsInput_.data());
}

int CStatisticsViewImpl::size() const {
  if (!StatisticsInput_.hasData())
    return 0;
  return static_cast<int>(StatisticsInput_.data().size());
}

const CStatisticsViewImpl::CDescription&
CStatisticsViewImpl::data_(int row) const {
  assert(size() > 0);
  return StatisticsInput_.data()[row];
}

} // namespace NSStatisticsViewDetail

} // namespace NSInterface
} // namespace NSApplication
