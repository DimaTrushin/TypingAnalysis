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
      ViewLocalizerInput_([this](const CViewLocalizer& Localizer) {
        setViewLocale(Localizer);
      }),
      StatisticsLocalizerInput_([this](const CStatisticsLocalizer& Localizer) {
        setStatisticsLocale(Localizer);
      }) {
  assert(TableView_);
  TableView_->setModel(&StatisticsModel_);
}

CStatisticsViewImpl::CTextDataObserver* CStatisticsViewImpl::textDataInput() {
  return &TextDataInput_;
}

CStatisticsViewImpl::CViewLocalizerObserver*
CStatisticsViewImpl::viewLocalizerInput() {
  return &ViewLocalizerInput_;
}

CStatisticsViewImpl::CStatisticsLocalizerObserver*
CStatisticsViewImpl::statisticsLocalizerInput() {
  return &StatisticsLocalizerInput_;
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
  const NSKernel::CTextDataTree& Tree = Data.textTree();

  Statistics.push_back(
      {printedTextLength(), QString::number(Tree->getPrintedTextLength())});
  Statistics.push_back(
      {fullTextLength(), QString::number(Tree->getFullTextLength())});
  Statistics.push_back(
      {deletedSymbols(), QString::number(Tree->getNumberOfDeletedSymbols())});
  Statistics.push_back(
      {mistakePlaces(), QString::number(Tree->getNumberOfMistakePlaces())});
  Statistics.push_back(
      {mistakes(), QString::number(Tree->getNumberOfMistakeRoutes())});
  Statistics.push_back(
      {mistakesPercent(), QString::number(Tree->percentOfMistakeRoutes())});
  Statistics.push_back(
      {printedTextDuration(),
       QString::number(Tree->getPrintedTextDuration().toSecondsF())});
  Statistics.push_back(
      {fullTextDuration(),
       QString::number(Tree->getFullTextDuration().toSecondsF())});
  Statistics.push_back(
      {printedTextSpeed(),
       QString::number(Tree->getPrintedTextLength() /
                       Tree->getPrintedTextDuration().toMinutesF())});
  Statistics.push_back(
      {fullTextSpeed(),
       QString::number(Tree->getFullTextLength() /
                       Tree->getFullTextDuration().toMinutesF())});
  return Statistics;
}

void CStatisticsViewImpl::setViewLocale(const CViewLocalizer& Localizer) {
  StatisticsModel_.setLocale(Localizer);
}

void CStatisticsViewImpl::setStatisticsLocale(const CStatisticsLocalizer&) {
  if (!TextDataInput_.hasValue())
    return;
  handleTextData(*TextDataInput_.data());
}

QString CStatisticsViewImpl::fullTextLength() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().fullTextLength();
}

QString CStatisticsViewImpl::printedTextLength() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().printedTextLength();
}

QString CStatisticsViewImpl::deletedSymbols() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().deletedSymbols();
}

QString CStatisticsViewImpl::mistakePlaces() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().mistakePlaces();
}

QString CStatisticsViewImpl::mistakes() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().mistakes();
}

QString CStatisticsViewImpl::mistakesPercent() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().mistakesPercent();
}

QString CStatisticsViewImpl::fullTextDuration() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().fullTextDuration();
}

QString CStatisticsViewImpl::printedTextDuration() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().printedTextDuration();
}

QString CStatisticsViewImpl::fullTextSpeed() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().fullTextSpeed();
}

QString CStatisticsViewImpl::printedTextSpeed() const {
  if (!StatisticsLocalizerInput_.hasValue())
    return "";
  return StatisticsLocalizerInput_.data()->get().printedTextSpeed();
}
} // namespace NSStatisticsViewDetail

} // namespace NSInterface
} // namespace NSApplication
