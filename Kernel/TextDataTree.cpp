#include "TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

CTextNode::CTextNode(QChar Symbol, ESymbolStatus Status)
    : Symbol_(Symbol), SymbolStatus_(Status) {
}

// bool CTextNode::isTextDelimiter() const {
//  return (pKeyEvent_ != nullptr) &&
//         (pKeyEvent_->isSpacebar() || pKeyEvent_->isEnter());
//}

// bool CTextNode::isSymbol() const {
//  return (pKeyEvent_ != nullptr) && pKeyEvent_->isSymbolKey();
//}

// bool CTextNode::isAnyDeleted() const {
//  return SymbolStatus_ == ESymbolStatus::DeletedSymbolAccidental ||
//         SymbolStatus_ == ESymbolStatus::DeletedSymbolRequired;
//}

// bool CTextNode::isAnyPrinted() const {
//  return SymbolStatus_ == ESymbolStatus::TextSymbol ||
//         SymbolStatus_ == ESymbolStatus::ErroneousSymbol;
//}

// CTime CTextNode::getPressingTime() const {
//  if (pKeyEvent_ == nullptr)
//    return 0;
//  return pKeyEvent_->getPressingTime();
//}

// CTime CTextNode::getReleasingTime() const {
//  if (pKeyEvent_ == nullptr)
//    return 0;
//  return pKeyEvent_->getReleasingTime();
//}

// CTime CTextNode::getResponseTime() const {
//  return ResponseTime_;
//}

// CTime CTextNode::getDurationTime() const {
//  if (pKeyEvent_ == nullptr)
//    return 0;
//  return pKeyEvent_->getDurationTime();
//}

QChar CTextNode::getSymbol() const {
  return Symbol_;
}

ESymbolStatus CTextNode::getSymbolStatus() const {
  return SymbolStatus_;
}

void CTextNode::setSymbolStatus(ESymbolStatus newStatus) {
  SymbolStatus_ = newStatus;
}

namespace NSTextDataTreeDetail {

void CTextDataTreeImpl::clear() {
  Tree_.destroyExceptRoot();
  //  getRootNode().Data_.MistakeRoutes_.clear();
  FinalElement_ = rootIterator();
}

void CTextDataTreeImpl::add(QChar Symbol, ESymbolStatus Status) {
  addData(CTextNode(Symbol, Status));
}

void CTextDataTreeImpl::addData(const CTextNode& TextData) {
  FinalElement_.addLastChild(TextData);
  ++FinalElement_;
}

void CTextDataTreeImpl::addData(CTextNode&& TextData) {
  FinalElement_.addLastChild(std::move(TextData));
  ++FinalElement_;
}

void CTextDataTreeImpl::deleteLastData() {
  if (FinalElement_.isRoot())
    return;
  FinalElement_->setSymbolStatus(ESymbolStatus::DeletedSymbolAccidental);
  --FinalElement_;
}

// void CTextDataTree::deleteLastBlock() {
//  deleteLastTextDelimiterBlock();
//  deleteLastSymbolBlock();
//}

CTextDataTreeImpl::CIndex
CTextDataTreeImpl::getNumberOfPlacesWithDeletion() const {
  if (Tree_.size() == 1)
    return 0;
  CConstTextIterator index = rootIterator();
  CIndex places = 0;
  while (index != FinalElement_) {
    if (index.getNumberOfChildren() > 1)
      places += 1;
    ++index;
  }
  if (index.getNumberOfChildren() > 0)
    places += 1;
  return places;
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::getNumberOfDeletionSeries() const {
  if (Tree_.size() == 1)
    return 0;
  CConstTextIterator index;
  index = rootIterator();
  CIndex places = 0;
  while (index != FinalElement_) {
    places += index.getNumberOfChildren() - 1;
    ++index;
  }
  places += index.getNumberOfChildren();
  return places;
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::getNumberOfDeletedSymbols() const {
  CIndex numberOfDeletedSymbols = 0;
  for (CConstTextIterator itCurrentSymbol = rootIterator();
       itCurrentSymbol != FinalElement_; ++itCurrentSymbol)
    for (auto child = itCurrentSymbol.FirstChild();
         child != itCurrentSymbol.LastChild(); ++child)
      numberOfDeletedSymbols += child.getSizeOfSubTree();
  numberOfDeletedSymbols += FinalElement_.getSizeOfSubTree() - 1;
  return numberOfDeletedSymbols;
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::getNumberOfReturnPoints() const {
  if (FinalElement_.hasChildren())
    return rootIterator().getNumberOfLeaves();
  return rootIterator().getNumberOfLeaves() - 1;
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::getTotalNumberOfSymbols() const {
  return Tree_.size();
}

// CTextDataTree::CIndex CTextDataTree::getTextLength(ETextMode TextMode) const
// {
//  if (TextMode == ETextMode::Full)
//    return getFullTextLength();
//  assert(TextMode == ETextMode::Printed);
//  return getPrintedTextLength();
//}

// CTextDataTree::CIndex CTextDataTree::getDeletionSeriesLengthSupremum() const
// {
//  CIndex lengthsup = 0;
//  for (CConstTextIterator itCurrentSymbol = beginFromRoot();
//       itCurrentSymbol != FinalElement_; ++itCurrentSymbol)
//    for (auto child = itCurrentSymbol.FirstChild();
//         child != itCurrentSymbol.LastChild(); ++child)
//      lengthsup = std::max(lengthsup, child.getLengthOfSubTree());
//  lengthsup = std::max(lengthsup, FinalElement_.getLengthOfSubTree() - 1);
//  return lengthsup;
//}

//// symbols deleted at the end are assumed to be mistakes
// CTextDataTree::CIndex CTextDataTree::getNumberOfMistakePlaces() const {
//  CIndex mistakePlaces = 0;
//  for (CConstTextIterator index = beginFromRoot(); index != endPrintedText();
//       ++index)
//    if (!index->MistakeRoutes_.empty())
//      ++mistakePlaces;
//  return mistakePlaces;
//}

//// symbols deleted at the end are assumed to be mistakes
// CTextDataTree::CIndex CTextDataTree::getNumberOfMistakeRoutes() const {
//  CIndex mistakes = 0;
//  for (CConstTextIterator index = beginFromRoot(); index != endPrintedText();
//       ++index)
//    mistakes += index->MistakeRoutes_.size();
//  return mistakes;
//}

// symbols deleted at the end are assumed to be mistakes
// CTextDataTree::CIndex CTextDataTree::getMistakeRoutesLengthSupremum() const {
//  CIndex lengthSupremum = 0;
//  for (CConstTextIterator index = beginFromRoot(); index != endPrintedText();
//       ++index)
//    for (auto itMistakeRoute = index->MistakeRoutes_.cbegin();
//         itMistakeRoute != index->MistakeRoutes_.end(); ++itMistakeRoute)
//      lengthSupremum =
//          std::max(lengthSupremum, itMistakeRoute->getLengthOfSubTree());
//  return lengthSupremum;
//}

// bool CTextDataTree::isTextEmpty(ETextMode TextMode) const {
//  if (getTextLength(TextMode) == 0)
//    return true;
//  return false;
//}

// microseconds CTextDataTree::getFirstPressingTime(ETextMode TextMode) const {
//  if (isTextEmpty(TextMode))
//    return 0;
//  return beginText(TextMode)->getPressingTime();
//}

// microseconds CTextDataTree::getLastPressingTime(ETextMode TextMode) const {
//  if (TextMode == ETextMode::Full)
//    return getLastFullTextPressingTime();
//  assert(TextMode == ETextMode::Printed);
//  return getLastPrintedTextPressingTime();
//}

// microseconds CTextDataTree::getTextDurationTime(ETextMode TextMode) const {
//  if (isTextEmpty(TextMode))
//    return 0;
//  return getLastPressingTime(TextMode) - getFirstPressingTime(TextMode);
//}

// CTextDataTree::CConstBasicIterator
// CTextDataTree::beginText(ETextMode TextMode) const {
//  if (TextMode == ETextMode::Full)
//    return beginFullText();
//  assert(TextMode == ETextMode::Printed);
//  return beginPrintedText();
//}

// CTextDataTree::CBasicIterator CTextDataTree::beginText(ETextMode TextMode) {
//  if (TextMode == ETextMode::Full)
//    return beginFullText();
//  assert(TextMode == ETextMode::Printed);
//  return beginPrintedText();
//}

// CTextDataTree::CConstBasicIterator
// CTextDataTree::endText(ETextMode TextMode) const {
//  if (TextMode == ETextMode::Full)
//    return endFullText();
//  assert(TextMode == ETextMode::Printed);
//  return endPrintedText();
//}

// CTextDataTree::CBasicIterator CTextDataTree::endText(ETextMode TextMode) {
//  if (TextMode == ETextMode::Full)
//    return endFullText();
//  assert(TextMode == ETextMode::Printed);
//  return endPrintedText();
//}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::rootIterator() const {
  return Tree_.begin();
}

CTextDataTreeImpl::CFullTextIterator CTextDataTreeImpl::rootIterator() {
  return Tree_.begin();
}

bool CTextDataTreeImpl::isStateCorrect_() const {
  return Tree_.isStateCorrect_();
}

// microseconds CTextDataTree::getLastPrintedTextPressingTime() const {
//  if (isTextEmpty(ETextMode::Printed))
//    return 0;
//  return FinalElement_->getPressingTime();
//}

// microseconds CTextDataTree::getLastFullTextPressingTime() const {
//  if (isTextEmpty(ETextMode::Full))
//    return 0;
//  return (--endPreOrder())->getPressingTime();
//}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::beginPrintedText() const {
  CConstTextIterator TextBeginning = rootIterator();
  return ++TextBeginning;
}

CTextDataTreeImpl::CTextIterator CTextDataTreeImpl::beginPrintedText() {
  CTextIterator TextBeginning = rootIterator();
  return ++TextBeginning;
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::beginFullText() const {
  CConstFullTextIterator TextBeginning = rootIterator();
  return ++TextBeginning;
}

CTextDataTreeImpl::CFullTextIterator CTextDataTreeImpl::beginFullText() {
  CFullTextIterator TextBeginning = rootIterator();
  return ++TextBeginning;
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::endPrintedText() const {
  CConstTextIterator TextEnding = FinalElement_;
  return ++TextEnding;
}

CTextDataTreeImpl::CTextIterator CTextDataTreeImpl::endPrintedText() {
  CTextIterator TextEnding = FinalElement_;
  return ++TextEnding;
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::endFullText() const {
  return Tree_.endPreOrder();
}

CTextDataTreeImpl::CFullTextIterator CTextDataTreeImpl::endFullText() {
  return Tree_.endPreOrder();
}

// void CTextDataTree::setFinalElement(const CTextDataTree& Tree) {
//  CIndex difference =
//      Tree.FinalElement_ - CConstTextIterator(Tree.beginFromRoot());
//  FinalElement_ = beginFromRoot();
//  FinalElement_ += difference;
//}

// void CTextDataTree::setFinalElementHost() {
//  FinalElement_.changeHost(this);
//}

// CIndex CTextDataTree::getPrintedTextLength() const {
//  return endPrintedText() - beginPrintedText();
//}

// CIndex CTextDataTree::getFullTextLength() const {
//  return size() - 1;
//}

// void CTextDataTree::deleteLastTextDelimiterBlock() {
//  //  while (FinalElement_->isTextDelimiter())
//  //    deleteLastData();
//}

// void CTextDataTree::deleteLastSymbolBlock() {
//  //  while (FinalElement_->isSymbol())
//  //    deleteLastData();
//}
} // namespace NSTextDataTreeDetail
} // namespace NSKernel
} // namespace NSApplication
