#include "StatisticsModule.h"

namespace NSApplication {
namespace NSKernel {
namespace NSStatisticsModuleDetail {

CStatisticsModuleImpl::CStatisticsModuleImpl()
    : LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }),
      AnalyticDataInput_(
          [this](const CAnalyticData& Data) { handleAnalyticData(Data); }) {
}

CStatisticsModuleImpl::CAnalyticDataObserver*
CStatisticsModuleImpl::analyticDataInput() {
  return &AnalyticDataInput_;
}

CStatisticsModuleImpl::CLocalizerInput*
CStatisticsModuleImpl::localizerInput() {
  return &LocalizerInput_;
}

void CStatisticsModuleImpl::subscribeToStatisticsDescription(
    CStatisticsDescriptionObserver* obs) {
  StatisticsDescriptionOutput_.subscribe(obs);
}

void CStatisticsModuleImpl::setLocale(const CLocalizer&) {
  if (!AnalyticDataInput_.hasData())
    return;
  handleAnalyticData(AnalyticDataInput_.data_());
}

void CStatisticsModuleImpl::handleAnalyticData(const CAnalyticData& Data) {
  CStatisticsDescription Statistics;
  const NSKernel::CTextDataTree& Tree = Data.textData().textTree();

  Statistics.push_back({printedTextLength(),
                        QString::number(Tree->getPrintedTextLength()),
                        printedTextLengthHint()});
  Statistics.push_back({fullTextLength(),
                        QString::number(Tree->getFullTextLength()),
                        fullTextLengthHint()});
  Statistics.push_back({deletedSymbols(),
                        QString::number(Tree->getNumberOfDeletedSymbols()),
                        deletedSymbolsHint()});
  Statistics.push_back({mistakePlaces(),
                        QString::number(Tree->getNumberOfMistakePlaces()),
                        mistakePlacesHint()});
  Statistics.push_back({mistakes(),
                        QString::number(Tree->getNumberOfMistakeRoutes()),
                        mistakesHint()});
  Statistics.push_back(
      {mistakesPercent(),
       QString::number(Tree->percentOfMistakeRoutes(), 'f', 2) + QString(" %"),
       mistakesPercentHint()});
  Statistics.push_back(
      {printedTextDuration(),
       QString::number(Tree->getPrintedTextDuration().toSecondsF(), 'f', 2),
       printedTextDurationHint()});
  Statistics.push_back(
      {printedTextSpeed(),
       (Tree->getPrintedTextDuration().toMinutesF() > 0
            ? QString::number(Tree->getPrintedTextLength() /
                                  Tree->getPrintedTextDuration().toMinutesF(),
                              'f', 2)
            : "0"),
       printedTextSpeedHint()});
  Statistics.push_back({maxLikelihoodSpeed(),
                        QString::number(Data.plotData().max0().x),
                        maxLikelihoodSpeedHint()});
  Statistics.push_back(
      {score(), QString::number(Data.plotData().score()), scoreHint()});
  StatisticsDescriptionOutput_.set(std::move(Statistics));
}

QString CStatisticsModuleImpl::fullTextLength() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().fullTextLength();
}

QString CStatisticsModuleImpl::printedTextLength() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().printedTextLength();
}

QString CStatisticsModuleImpl::deletedSymbols() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().deletedSymbols();
}

QString CStatisticsModuleImpl::mistakePlaces() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().mistakePlaces();
}

QString CStatisticsModuleImpl::mistakes() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().mistakes();
}

QString CStatisticsModuleImpl::mistakesPercent() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().mistakesPercent();
}

QString CStatisticsModuleImpl::printedTextDuration() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().printedTextDuration();
}

QString CStatisticsModuleImpl::printedTextSpeed() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().printedTextSpeed();
}

QString CStatisticsModuleImpl::maxLikelihoodSpeed() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().maxLikelihoodSpeed();
}

QString CStatisticsModuleImpl::score() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().score();
}

QString CStatisticsModuleImpl::fullTextLengthHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().fullTextLengthHint();
}

QString CStatisticsModuleImpl::printedTextLengthHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().printedTextLengthHint();
}

QString CStatisticsModuleImpl::deletedSymbolsHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().deletedSymbolsHint();
}

QString CStatisticsModuleImpl::mistakePlacesHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().mistakePlacesHint();
}

QString CStatisticsModuleImpl::mistakesHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().mistakesHint();
}

QString CStatisticsModuleImpl::mistakesPercentHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().mistakesPercentHint();
}

QString CStatisticsModuleImpl::printedTextDurationHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().printedTextDurationHint();
}

QString CStatisticsModuleImpl::printedTextSpeedHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().printedTextSpeedHint();
}

QString CStatisticsModuleImpl::maxLikelihoodSpeedHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().maxLikelihoodSpeedHint();
}

QString CStatisticsModuleImpl::scoreHint() const {
  if (!LocalizerInput_.hasData())
    return "";
  return LocalizerInput_.data_().scoreHint();
}

} // namespace NSStatisticsModuleDetail
} // namespace NSKernel
} // namespace NSApplication
