#include "StatisticsModule.h"

namespace NSApplication {
namespace NSKernel {
namespace NSStatisticsModuleDetail {

CStatisticsModuleImpl::CStatisticsModuleImpl()
    : LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }),
      TextDataInput_(
          [this](const CTextData& TextData) { handleTextData(TextData); }) {
}

CStatisticsModuleImpl::CTextDataObserver*
CStatisticsModuleImpl::textDataInput() {
  return &TextDataInput_;
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
  if (!TextDataInput_.hasValue())
    return;
  handleTextData(*TextDataInput_.data());
}

void CStatisticsModuleImpl::handleTextData(const CTextData& Data) {
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
      {mistakesPercent(),
       QString::number(Tree->percentOfMistakeRoutes()) + QString(" %")});
  Statistics.push_back(
      {printedTextDuration(),
       QString::number(Tree->getPrintedTextDuration().toSecondsF())});
  Statistics.push_back(
      {printedTextSpeed(),
       QString::number(Tree->getPrintedTextLength() /
                       Tree->getPrintedTextDuration().toMinutesF())});
  StatisticsDescriptionOutput_.set(std::move(Statistics));
}

QString CStatisticsModuleImpl::fullTextLength() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().fullTextLength();
}

QString CStatisticsModuleImpl::printedTextLength() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().printedTextLength();
}

QString CStatisticsModuleImpl::deletedSymbols() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().deletedSymbols();
}

QString CStatisticsModuleImpl::mistakePlaces() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().mistakePlaces();
}

QString CStatisticsModuleImpl::mistakes() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().mistakes();
}

QString CStatisticsModuleImpl::mistakesPercent() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().mistakesPercent();
}

QString CStatisticsModuleImpl::fullTextDuration() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().fullTextDuration();
}

QString CStatisticsModuleImpl::printedTextDuration() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().printedTextDuration();
}

QString CStatisticsModuleImpl::fullTextSpeed() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().fullTextSpeed();
}

QString CStatisticsModuleImpl::printedTextSpeed() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().printedTextSpeed();
}

} // namespace NSStatisticsModuleDetail
} // namespace NSKernel
} // namespace NSApplication
