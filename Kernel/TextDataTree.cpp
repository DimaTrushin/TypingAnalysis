#include "TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

namespace NSTextDataTreeDetail {

CTextDataTreeImpl::CTextDataTreeImpl()
    : Tree_{CTextNode(QChar(), CTime(), CTime(), ESymbolStatus::RootSymbol,
                      CKeyPosEnum::UNKN, CTime())} {
}

void CTextDataTreeImpl::clear() {
  Tree_.destroyExceptRoot();
  Tree_.dataRoot().clearMistakeRoutes();
  FinalElement_ = rootIterator();
}

void CTextDataTreeImpl::add(QChar Symbol, CTime PressingTime, CTime ReleaseTime,
                            ESymbolStatus Status, CKeyPosition Position,
                            CTime ResponseTime) {
  addData(CTextNode(Symbol, PressingTime, ReleaseTime, Status, Position,
                    ResponseTime));
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

CTextDataTreeImpl::CIndex CTextDataTreeImpl::getTreeSize() const {
  return Tree_.size();
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::getPrintedTextLength() const {
  return FinalElement_.getDistanceToRoot();
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::getFullTextLength() const {
  return Tree_.size() - 1;
}

CTextDataTreeImpl::CIndex
CTextDataTreeImpl::getTextLength(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return getFullTextLength();
  assert(TextMode == ETextMode::Printed);
  return getPrintedTextLength();
}

CTextDataTreeImpl::CIndex
CTextDataTreeImpl::getDeletionSeriesLengthSupremum() const {
  CIndex lengthsup = 0;
  for (CConstTextIterator itCurrentSymbol = rootIterator();
       itCurrentSymbol != FinalElement_; ++itCurrentSymbol)
    for (auto child = itCurrentSymbol.FirstChild();
         child != itCurrentSymbol.LastChild(); ++child)
      lengthsup = std::max(lengthsup, child.getLengthOfSubTree());
  lengthsup = std::max(lengthsup, FinalElement_.getLengthOfSubTree() - 1);
  return lengthsup;
}

//// symbols deleted at the end are assumed to be mistakes
CTextDataTreeImpl::CIndex CTextDataTreeImpl::getNumberOfMistakePlaces() const {
  CIndex mistakePlaces = 0;
  for (CConstTextIterator index = rootIterator(); index != endPrintedText();
       ++index)
    if (!index->hasNoMistakeRoutes())
      ++mistakePlaces;
  return mistakePlaces;
}

//// symbols deleted at the end are assumed to be mistakes
CTextDataTreeImpl::CIndex CTextDataTreeImpl::getNumberOfMistakeRoutes() const {
  CIndex mistakes = 0;
  for (CConstTextIterator index = rootIterator(); index != endPrintedText();
       ++index)
    mistakes += index->numberOfMistakeRoutes();
  return mistakes;
}

// symbols deleted at the end are assumed to be mistakes
CTextDataTreeImpl::CIndex
CTextDataTreeImpl::getMistakeRoutesLengthSupremum() const {
  CIndex lengthSupremum = 0;
  for (CConstTextIterator index = rootIterator(); index != endPrintedText();
       ++index)
    for (auto itMistakeRoute = index->cbeginMistakes();
         itMistakeRoute != index->cendMistakes(); ++itMistakeRoute)
      lengthSupremum =
          std::max(lengthSupremum, itMistakeRoute->getLengthOfSubTree());
  return lengthSupremum;
}

double CTextDataTreeImpl::percentOfMistakeRoutes() const {
  if (getPrintedTextLength() == 0)
    return 0.;
  return static_cast<double>(getNumberOfMistakeRoutes()) * 100. /
         getPrintedTextLength();
}

bool CTextDataTreeImpl::isTextEmpty(ETextMode TextMode) const {
  if (getTextLength(TextMode) == 0)
    return true;
  return false;
}

CTime CTextDataTreeImpl::getFirstPressingTime(ETextMode TextMode) const {
  if (isTextEmpty(TextMode))
    return {};
  switch (TextMode) {
  case ETextMode::Full:
    return beginFullText()->getPressingTime();
  case ETextMode::Printed:
    return beginPrintedText()->getPressingTime();
  default:
    assert(false);
    return {};
  }
}

CTime CTextDataTreeImpl::getLastPressingTime(ETextMode TextMode) const {
  if (isTextEmpty(TextMode))
    return {};
  switch (TextMode) {
  case ETextMode::Full:
    return Tree_.data(Tree_.size() - 1).getPressingTime();
  case ETextMode::Printed:
    return FinalElement_->getPressingTime();
  default:
    assert(false);
    return {};
  }
}

CTime CTextDataTreeImpl::getTextDurationTime(ETextMode TextMode) const {
  if (isTextEmpty(TextMode))
    return {};
  return getLastPressingTime(TextMode) - getFirstPressingTime(TextMode);
}

CTime CTextDataTreeImpl::getPrintedTextDuration() const {
  if (getPrintedTextLength() == 0)
    return {};
  return FinalElement_->getPressingTime() -
         beginPrintedText()->getPressingTime();
}

CTime CTextDataTreeImpl::getFullTextDuration() const {
  if (getFullTextLength() == 0)
    return {};
  return Tree_.data(Tree_.size() - 1).getPressingTime() -
         beginFullText()->getPressingTime();
}

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
  setNodeDepths();
}

CTextDataTreeImpl::CFullTextProxy CTextDataTreeImpl::textFullView() {
  return CFullTextProxy(this);
}

CTextDataTreeImpl::CConstFullTextProxy
CTextDataTreeImpl::textConstFullView() const {
  return CConstFullTextProxy(this);
}

CTextDataTreeImpl::CPrintedTextProxy CTextDataTreeImpl::textPrintedView() {
  return CPrintedTextProxy(this);
}

CTextDataTreeImpl::CConstPrintedTextProxy
CTextDataTreeImpl::textConstPrintedView() const {
  return CConstPrintedTextProxy(this);
}

void CTextDataTreeImpl::setMistakeRoutes() {
  for (CTextIterator currentPosition = rootIterator();
       currentPosition != FinalElement_; ++currentPosition) {
    reAssignMistakeRoutes(currentPosition);
    assignNewMistakeRoutes(currentPosition);
  }
  assignMistakeRoutesForFinalElement();
}

void CTextDataTreeImpl::setMistakeSymbols() {
  for (CTextIterator itCurrentSymbol = rootIterator();
       itCurrentSymbol != FinalElement_; ++itCurrentSymbol)
    if (!itCurrentSymbol->hasNoMistakeRoutes())
      itCurrentSymbol.LastChild()->setSymbolStatus(
          ESymbolStatus::ErroneousSymbol);
}

void CTextDataTreeImpl::setRequiredDeleted() {
  for (CTextIterator currentPosition = rootIterator();
       currentPosition != endPrintedText(); ++currentPosition)
    for (auto itMistakeRoute = currentPosition->beginMistakes();
         itMistakeRoute != currentPosition->endMistakes(); ++itMistakeRoute)
      setRequiredDeletedFrom(*itMistakeRoute);
}

void CTextDataTreeImpl::setNodeDepths() {

  for (CFullTextIterator iter = rootIterator(); iter != endFullText(); ++iter) {
    CFullTextIterator parent;
    switch (iter->getSymbolStatus()) {
    case ESymbolStatus::TextSymbol:
      iter->setDepth(0);
      break;
    case ESymbolStatus::DeletedSymbolAccidental:
      parent = iter;
      parent.setToParent();
      if (parent->getSymbolStatus() == ESymbolStatus::DeletedSymbolAccidental)
        iter->setDepth(parent->getDepth() + 1);
      else
        iter->setDepth(0);
      break;
    case ESymbolStatus::DeletedSymbolRequired:
      parent = iter;
      parent.setToParent();
      if (parent->getSymbolStatus() == ESymbolStatus::DeletedSymbolRequired)
        iter->setDepth(parent->getDepth() + 1);
      else
        iter->setDepth(0);
      break;
    case ESymbolStatus::ErroneousSymbol:
      parent = iter;
      parent.setToParent();
      iter->setDepth(parent->numberOfMistakeRoutes());
      break;
    case ESymbolStatus::RootSymbol:
      iter->setDepth(0);
      break;
    default:
      assert(false);
      break;
    }
  }
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

void CTextDataTreeImpl::deleteLastTextDelimiterBlock() {
  while (FinalElement_->getSymbol().isPunct())
    deleteLastData();
}

void CTextDataTreeImpl::deleteLastSymbolBlock() {
  while (FinalElement_->getSymbol().isLetterOrNumber())
    deleteLastData();
}

CTextDataTreeImpl::CFullTextIterator
CTextDataTreeImpl::CFullTextProxy::begin() {
  return pTree_->beginFullText();
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CFullTextProxy::begin() const {
  return pTree_->beginFullText();
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CFullTextProxy::cbegin() const {
  return pTree_->beginFullText();
}

CTextDataTreeImpl::CFullTextIterator CTextDataTreeImpl::CFullTextProxy::end() {
  return pTree_->endFullText();
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CFullTextProxy::end() const {
  return pTree_->endFullText();
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CFullTextProxy::cend() const {
  return pTree_->endFullText();
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::CFullTextProxy::size() const {
  return pTree_->getFullTextLength();
}

bool CTextDataTreeImpl::CFullTextProxy::empty() const {
  return size() == 0;
}

CTextDataTreeImpl::CFullTextProxy::CFullTextProxy(CTextDataTreeImpl* pTree)
    : pTree_(pTree) {
  assert(pTree_);
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CConstFullTextProxy::begin() const {
  return pTree_->beginFullText();
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CConstFullTextProxy::cbegin() const {
  return pTree_->beginFullText();
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CConstFullTextProxy::end() const {
  return pTree_->endFullText();
}

CTextDataTreeImpl::CConstFullTextIterator
CTextDataTreeImpl::CConstFullTextProxy::cend() const {
  return pTree_->endFullText();
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::CConstFullTextProxy::size() const {
  return pTree_->getFullTextLength();
}

bool CTextDataTreeImpl::CConstFullTextProxy::empty() const {
  return size() == 0;
}

CTextDataTreeImpl::CConstFullTextProxy::CConstFullTextProxy(
    const CTextDataTreeImpl* pTree)
    : pTree_(pTree) {
  assert(pTree_);
}

CTextDataTreeImpl::CTextIterator CTextDataTreeImpl::CPrintedTextProxy::begin() {
  return pTree_->beginPrintedText();
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CPrintedTextProxy::begin() const {
  return pTree_->beginPrintedText();
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CPrintedTextProxy::cbegin() const {
  return pTree_->beginPrintedText();
}

CTextDataTreeImpl::CTextIterator CTextDataTreeImpl::CPrintedTextProxy::end() {
  return pTree_->endPrintedText();
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CPrintedTextProxy::end() const {
  return pTree_->endPrintedText();
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CPrintedTextProxy::cend() const {
  return pTree_->endPrintedText();
}

CTextDataTreeImpl::CIndex CTextDataTreeImpl::CPrintedTextProxy::size() const {
  return pTree_->getPrintedTextLength();
}

bool CTextDataTreeImpl::CPrintedTextProxy::empty() const {
  return size() == 0;
}

CTextDataTreeImpl::CPrintedTextProxy::CPrintedTextProxy(
    CTextDataTreeImpl* pTree)
    : pTree_(pTree) {
  assert(pTree_);
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CConstPrintedTextProxy::begin() const {
  return pTree_->beginPrintedText();
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CConstPrintedTextProxy::cbegin() const {
  return pTree_->beginPrintedText();
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CConstPrintedTextProxy::end() const {
  return pTree_->endPrintedText();
}

CTextDataTreeImpl::CConstTextIterator
CTextDataTreeImpl::CConstPrintedTextProxy::cend() const {
  return pTree_->endPrintedText();
}

CTextDataTreeImpl::CIndex
CTextDataTreeImpl::CConstPrintedTextProxy::size() const {
  return pTree_->getPrintedTextLength();
}

bool CTextDataTreeImpl::CConstPrintedTextProxy::empty() const {
  return size() == 0;
}

CTextDataTreeImpl::CConstPrintedTextProxy::CConstPrintedTextProxy(
    const CTextDataTreeImpl* pTree)
    : pTree_(pTree) {
  assert(pTree_);
}

} // namespace NSTextDataTreeDetail

CTextNode::CTextNode(QChar Symbol, CTime PressingTime, CTime ReleaseTime,
                     ESymbolStatus Status, CKeyPosition Position,
                     CTime ResponseTime)
    : PressingTime_(PressingTime), ReleaseTime_(ReleaseTime),
      ResponseTime_(ResponseTime), Symbol_(Symbol), SymbolStatus_(Status),
      KeyPosition_(Position) {
}

CTime CTextNode::getPressingTime() const {
  return PressingTime_;
}

CTime CTextNode::getReleasingTime() const {
  return ReleaseTime_;
}

CTime CTextNode::getResponseTime() const {
  return ResponseTime_;
}

CTime CTextNode::getDurationTime() const {
  return ReleaseTime_ - PressingTime_;
}

QChar CTextNode::getSymbol() const {
  return Symbol_;
}

ESymbolStatus CTextNode::getSymbolStatus() const {
  return SymbolStatus_;
}

unsigned char CTextNode::getDepth() const {
  return Depth_;
}

void CTextNode::setSymbolStatus(ESymbolStatus newStatus) {
  SymbolStatus_ = newStatus;
}

void CTextNode::setDepth(unsigned char Depth) {
  Depth_ = Depth;
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

bool CTextNode::hasNoMistakeRoutes() const {
  return MistakeRoutes_.empty();
}

void CTextNode::addMistakeRoute(CFullTextIterator iter) {
  MistakeRoutes_.push_back(std::move(iter));
}

CTextNode::CIndex CTextNode::numberOfMistakeRoutes() const {
  return MistakeRoutes_.size();
}

CTextNode::CKeyPosition CTextNode::getPosition() const {
  return KeyPosition_;
}

} // namespace NSKernel
} // namespace NSApplication
