#include "TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

namespace NSTextDataTreeDetail {

CTextDataTreeImpl::CTextDataTreeImpl()
    : Tree_{CTextNode(QChar(), ESymbolStatus::RootSymbol)} {
}

void CTextDataTreeImpl::clear() {
  Tree_.destroyExceptRoot();
  Tree_.dataRoot().clearMistakeRoutes();
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

void CTextDataTreeImpl::deleteLastBlock() {
  // TO DO
  // neet to make the behaviour more adequate
  deleteLastTextDelimiterBlock();
  deleteLastSymbolBlock();
}

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

void CTextDataTreeImpl::setMistakeInformation() {
  setMistakeRoutes();
  setMistakeSymbols();
  setRequiredDeleted();
}

void CTextDataTreeImpl::setMistakeRoutes() {
  for (CTextIterator currentPosition = Tree_.begin();
       currentPosition != FinalElement_; ++currentPosition) {
    reAssignMistakeRoutes(currentPosition);
    assignNewMistakeRoutes(currentPosition);
  }
  assignMistakeRoutesForFinalElement();
}

void CTextDataTreeImpl::setMistakeSymbols() {
  for (CTextIterator itCurrentSymbol = Tree_.begin();
       itCurrentSymbol != FinalElement_; ++itCurrentSymbol)
    if (!itCurrentSymbol->hasNoMistakeRouts())
      itCurrentSymbol.LastChild()->setSymbolStatus(
          ESymbolStatus::ErroneousSymbol);
}

void CTextDataTreeImpl::setRequiredDeleted() {
  for (CTextIterator currentPosition = Tree_.begin();
       currentPosition != endPrintedText(); ++currentPosition)
    for (auto itMistakeRoute = currentPosition->beginMistakes();
         itMistakeRoute != currentPosition->endMistakes(); ++itMistakeRoute)
      setRequiredDeletedFrom(*itMistakeRoute);
}

void CTextDataTreeImpl::reAssignMistakeRoutes(
    const CTextIterator& currentPosition) {
  auto itMistakeRoute = currentPosition->beginMistakes();
  CTextIterator next = currentPosition;
  ++next;
  while (itMistakeRoute != currentPosition->endMistakes()) {
    if (next->getSymbol() == (*itMistakeRoute)->getSymbol()) {
      // we did not make a mistake in the next symbol
      // need to pass mistake routes to the node with the next symbol
      if (itMistakeRoute->hasChildren()) {
        // if there are mistake routes
        reAssignChildernTo(*itMistakeRoute, &next);
      }
      // remove itMistakeRoute from the current node of the tree
      itMistakeRoute = currentPosition->eraseMistakeNode(itMistakeRoute);
      continue;
    }
    ++itMistakeRoute;
  }
}

void CTextDataTreeImpl::assignNewMistakeRoutes(
    const CTextIterator& currentPosition) {
  CTextIterator currentNode(currentPosition);
  auto itMistakeRoute = currentNode.FirstChild();

  CTextIterator nextNode = currentPosition;
  ++nextNode;
  while (itMistakeRoute != currentNode.LastChild()) {
    if (nextNode->getSymbol() == itMistakeRoute->getSymbol()) {
      // If the symbol is the same, we did NOT make a mistake in the next symbol
      // if there are children, send them to the nextNode's MistakeRoutes
      if (itMistakeRoute.hasChildren()) {
        reAssignChildernTo(itMistakeRoute, &nextNode);
      }
    } else {
      // if the symbol is NOT the same, we made a mistake in the next symbol
      // need to write the current route to the MistakeRoutes of the currentNode
      currentPosition->addMistakeRoute(itMistakeRoute);
    }
    ++itMistakeRoute;
  }
}

void CTextDataTreeImpl::assignMistakeRoutesForFinalElement() {
  if (!FinalElement_.hasChildren())
    return;
  for (auto itMistakeRoute = FinalElement_.FirstChild();
       itMistakeRoute != FinalElement_.LastChild(); ++itMistakeRoute)
    FinalElement_->addMistakeRoute(itMistakeRoute);
  FinalElement_->addMistakeRoute(FinalElement_.LastChild());
}

void CTextDataTreeImpl::reAssignChildernTo(const CTextIterator& source,
                                           CTextIterator* target) {
  for (auto itChild = source.FirstChild(); itChild != source.LastChild();
       ++itChild)
    (*target)->addMistakeRoute(itChild);
  (*target)->addMistakeRoute(source.LastChild());
}

void CTextDataTreeImpl::setRequiredDeletedFrom(
    const CSiblingIterator& currentNode) {
  currentNode->setSymbolStatus(ESymbolStatus::DeletedSymbolRequired);

  if (!currentNode.hasChildren())
    return;
  for (auto itChild = currentNode.FirstChild();
       itChild != currentNode.LastChild(); ++itChild)
    setRequiredDeletedFrom(itChild);
  setRequiredDeletedFrom(currentNode.LastChild());
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

void CTextDataTreeImpl::deleteLastTextDelimiterBlock() {
  while (FinalElement_->getSymbol().isPunct())
    deleteLastData();
}

void CTextDataTreeImpl::deleteLastSymbolBlock() {
  while (FinalElement_->getSymbol().isLetterOrNumber())
    deleteLastData();
}
} // namespace NSTextDataTreeDetail

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

void CTextNode::clearMistakeRoutes() {
  MistakeRoutes_.clear();
}

CTextNode::CMistakeIterator CTextNode::beginMistakes() {
  return MistakeRoutes_.begin();
}

CTextNode::CConstMistakeIterator CTextNode::beginMistakes() const {
  return MistakeRoutes_.begin();
}

CTextNode::CConstMistakeIterator CTextNode::cbeginMistakes() const {
  return MistakeRoutes_.cbegin();
}

CTextNode::CMistakeIterator CTextNode::endMistakes() {
  return MistakeRoutes_.end();
}

CTextNode::CConstMistakeIterator CTextNode::endMistakes() const {
  return MistakeRoutes_.end();
}

CTextNode::CConstMistakeIterator CTextNode::cendMistakes() const {
  return MistakeRoutes_.cend();
}

CTextNode::CMistakeIterator
CTextNode::eraseMistakeNode(CConstMistakeIterator Current) {
  return MistakeRoutes_.erase(Current);
}

bool CTextNode::hasNoMistakeRouts() const {
  return MistakeRoutes_.empty();
}

void CTextNode::addMistakeRoute(CFullTextIterator iter) {
  MistakeRoutes_.push_back(std::move(iter));
}

} // namespace NSKernel
} // namespace NSApplication
