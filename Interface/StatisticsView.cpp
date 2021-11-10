#include "StatisticsView.h"
#include <cassert>

#include <QDebug>
#include <QTableView>

#include <TimerAccess.h>

namespace NSApplication {
namespace NSInterface {

namespace NSStatisticsViewDetail {

CStatisticsViewImpl::CStatisticsViewImpl(QTableView* TableView)
    : TableView_(TableView),
      TextDataInput_([this](const CTextData& Data) { handleTextData(Data); }) {
  assert(TableView_);
  TableView_->setModel(&StatisticsModel_);
}

CStatisticsViewImpl::CTextDataObserver* CStatisticsViewImpl::textDataInput() {
  return &TextDataInput_;
}

void CStatisticsViewImpl::handleTextData(const CTextData& Data) {
  qDebug() << "CStatisticsViewImpl::handleTextData";
  CTime time = CTimerAccess()->get();
  StatisticsModel_.setStatistics(Data);
  time = CTimerAccess()->get() - time;
  qDebug() << "CStatisticsViewImpl::handleTextData time = "
           << time.toMicroSecondsI() << "mc";
}
} // namespace NSStatisticsViewDetail

} // namespace NSInterface
} // namespace NSApplication
