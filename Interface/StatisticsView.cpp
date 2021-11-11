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
  // TO DO
  // Need to
  // 1) make a separate object to make statistics
  StatisticsModel_.setStatistics(createStatisticsData(Data));
  time = CTimerAccess()->get() - time;
  qDebug() << "CStatisticsViewImpl::handleTextData time = "
           << time.toMicroSecondsI() << "mc";
}

CStatisticsViewImpl::CStatisticsDescription
CStatisticsViewImpl::createStatisticsData(const CTextData& Data) {
  CStatisticsDescription Statistics;
  Statistics.push_back(
      {"Places With Deletion",
       QString::number(Data.TextTree.get()->getNumberOfPlacesWithDeletion())});
  Statistics.push_back(
      {"Deletion Series",
       QString::number(Data.TextTree.get()->getNumberOfDeletionSeries())});
  Statistics.push_back(
      {"Deleted Symbols",
       QString::number(Data.TextTree.get()->getNumberOfDeletedSymbols())});
  Statistics.push_back(
      {"Return Points",
       QString::number(Data.TextTree.get()->getNumberOfReturnPoints())});
  Statistics.push_back(
      {"Tree size", QString::number(Data.TextTree.get()->getTreeSize())});
  Statistics.push_back(
      {"Deletion Length Supremum",
       QString::number(
           Data.TextTree.get()->getDeletionSeriesLengthSupremum())});
  Statistics.push_back(
      {"Mistake Places",
       QString::number(Data.TextTree.get()->getNumberOfMistakePlaces())});
  Statistics.push_back(
      {"Mistake Routes",
       QString::number(Data.TextTree.get()->getNumberOfMistakeRoutes())});
  Statistics.push_back(
      {"Mistake Route Length Supremum",
       QString::number(Data.TextTree.get()->getMistakeRoutesLengthSupremum())});
  return Statistics;
}
} // namespace NSStatisticsViewDetail

} // namespace NSInterface
} // namespace NSApplication
