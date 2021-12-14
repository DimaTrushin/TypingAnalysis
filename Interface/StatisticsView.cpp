#include "StatisticsView.h"
#include <cassert>

#include "AppDebug/PerformanceLogger.h"
#include "TimerAccess.h"

#include <QTableView>

namespace NSApplication {
namespace NSInterface {

namespace NSStatisticsViewDetail {

CStatisticsViewImpl::CStatisticsViewImpl(QTableView* TableView)
    : TableView_(TableView),
      TextDataInput_([this](const CTextData& Data) { handleTextData(Data); }),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }) {
  assert(TableView_);
  TableView_->setModel(&StatisticsModel_);
}

CStatisticsViewImpl::CTextDataObserver* CStatisticsViewImpl::textDataInput() {
  return &TextDataInput_;
}

CStatisticsViewImpl::CLocalizerObserver* CStatisticsViewImpl::localizerInput() {
  return &LocalizerInput_;
}

void CStatisticsViewImpl::handleTextData(const CTextData& Data) {
  NSAppDebug::CTimeAnchor Anchor("handle textData & notify time =");
  // TO DO
  // Need to
  // 1) make a separate object to make statistics
  StatisticsModel_.setStatistics(createStatisticsData(Data));
}

CStatisticsViewImpl::CStatisticsDescription
CStatisticsViewImpl::createStatisticsData(const CTextData& Data) {
  CStatisticsDescription Statistics;
  Statistics.push_back(
      {"Places With Deletion",
       QString::number(Data.textTree()->getNumberOfPlacesWithDeletion())});
  Statistics.push_back(
      {"Deletion Series",
       QString::number(Data.textTree()->getNumberOfDeletionSeries())});
  Statistics.push_back(
      {"Deleted Symbols",
       QString::number(Data.textTree()->getNumberOfDeletedSymbols())});
  Statistics.push_back(
      {"Return Points",
       QString::number(Data.textTree()->getNumberOfReturnPoints())});
  Statistics.push_back(
      {"Tree size", QString::number(Data.textTree()->getTreeSize())});
  Statistics.push_back(
      {"Deletion Length Supremum",
       QString::number(Data.textTree()->getDeletionSeriesLengthSupremum())});
  Statistics.push_back(
      {"Mistake Places",
       QString::number(Data.textTree()->getNumberOfMistakePlaces())});
  Statistics.push_back(
      {"Mistake Routes",
       QString::number(Data.textTree()->getNumberOfMistakeRoutes())});
  Statistics.push_back(
      {"Mistake Route Length Supremum",
       QString::number(Data.textTree()->getMistakeRoutesLengthSupremum())});
  return Statistics;
}

void CStatisticsViewImpl::setLocale(const CLocalizer& Localizer) {
  StatisticsModel_.setLocale(Localizer);
}
} // namespace NSStatisticsViewDetail

} // namespace NSInterface
} // namespace NSApplication
