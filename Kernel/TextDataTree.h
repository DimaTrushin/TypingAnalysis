#ifndef NSAPPLICATION_NSKERNEL_CTEXTDATATREE_H
#define NSAPPLICATION_NSKERNEL_CTEXTDATATREE_H

#include "Keyboard/KeyPosition.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Library/StlExtension/VTree.h"
#include "TextMode.h"
#include "TimeApp.h"

#include <list>

#include <QChar>

namespace NSApplication {
namespace NSKernel {

// RootSymbol -- symbol stored in the root of the tree
// DeletedSymbolAccidental -- deleted symbol that is NOT mistake
// DeletedSymbolRequired -- deleted symbol that is mistake
// TextSymbol -- printed symbol that is NOT the one where we made a mistake
// ErroneousSymbol -- printed symbol that is the one where we made a mistake
enum class ESymbolStatus : unsigned char {
  TextSymbol,
  DeletedSymbolAccidental,
  DeletedSymbolRequired,
  ErroneousSymbol,
  RootSymbol
};

template<class TOut>
TOut& operator<<(TOut& out, ESymbolStatus s) {
  switch (s) {
  case ESymbolStatus::TextSymbol:
    out << "TS";
    break;
  case ESymbolStatus::DeletedSymbolAccidental:
    out << "DSA";
    break;
  case ESymbolStatus::DeletedSymbolRequired:
    out << "DSR";
    break;
  case ESymbolStatus::ErroneousSymbol:
    out << "MS";
    break;
  case ESymbolStatus::RootSymbol:
    out << "RS";
    break;
  default:
    break;
  }
  return out;
}

class CTextNode;

namespace NSTextDataTreeDetail {

// The TextDataTree always has a root
class CTextDataTreeImpl {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyPosEnum = NSKeyboard::CKeyPosEnum;

public:
  using CTree = NSLibrary::CVTree<CTextNode>;
  using CIndex = int64_t;

  using CConstFullTextIterator = CTree::CConstPreOrderIterator;
  using CFullTextIterator = CTree::CPreOrderIterator;
  using CConstTextIterator = CTree::CConstLastSonIterator;
  using CTextIterator = CTree::CLastSonIterator;
  using CConstSiblingIterator = CTree::CConstSiblingIterator;
  using CSiblingIterator = CTree::CSiblingIterator;

  // These two iterators do not have a travel logic
  // They denote the begin and the end of a text
  // with a chosen TextMode
  using CConstBasicIterator = CTree::CConstBasicIterator;
  using CBasicIterator = CTree::CBasicIterator;

  CTextDataTreeImpl();
  CTextDataTreeImpl(const CTextDataTreeImpl&) = delete;
  CTextDataTreeImpl(CTextDataTreeImpl&&) noexcept = delete;
  CTextDataTreeImpl& operator=(const CTextDataTreeImpl&) = delete;
  CTextDataTreeImpl& operator=(CTextDataTreeImpl&&) noexcept = delete;

  void clear();
  void add(QChar Symbol, CTime PressingTime, CTime ReleaseTime,
           ESymbolStatus Status, CKeyPosition Position, CTime ResponseTime);
  void addData(const CTextNode& TextData);
  void addData(CTextNode&& TextData);
  // action for Backspace
  void deleteLastData();
  // action for Ctrl + Backspace
  void deleteLastBlock();

  CIndex getNumberOfPlacesWithDeletion() const;
  CIndex getNumberOfDeletionSeries() const;
  CIndex getNumberOfDeletedSymbols() const;
  // The number of times text deleting begins
  CIndex getNumberOfReturnPoints() const;
  //  // including the root symbol
  CIndex getTreeSize() const;

  CIndex getPrintedTextLength() const;
  CIndex getFullTextLength() const;

  CIndex getTextLength(ETextMode TextMode) const;
  CIndex getDeletionSeriesLengthSupremum() const;
  CIndex getNumberOfMistakePlaces() const;
  CIndex getNumberOfMistakeRoutes() const;
  CIndex getMistakeRoutesLengthSupremum() const;
  double percentOfMistakeRoutes() const;

  bool isTextEmpty(ETextMode TextMode) const;
  CTime getFirstPressingTime(ETextMode TextMode) const;
  CTime getLastPressingTime(ETextMode TextMode) const;
  CTime getTextDurationTime(ETextMode TextMode) const;

  CTime getPrintedTextDuration() const;
  CTime getFullTextDuration() const;

  //  CConstBasicIterator beginText(ETextMode TextMode) const;
  //  CBasicIterator beginText(ETextMode TextMode);
  //  CConstBasicIterator endText(ETextMode TextMode) const;
  //  CBasicIterator endText(ETextMode TextMode);
  CConstFullTextIterator rootIterator() const;
  CFullTextIterator rootIterator();

  template<class TOut>
  friend TOut& operator<<(TOut& out, const CTextDataTreeImpl& tree) {
    out << tree.Tree_;
    return out;
  }

  bool isStateCorrect_() const;

  //  CTime getLastPrintedTextPressingTime() const;
  //  CTime getLastFullTextPressingTime() const;

  CConstTextIterator beginPrintedText() const;
  CTextIterator beginPrintedText();
  CConstFullTextIterator beginFullText() const;
  CFullTextIterator beginFullText();
  CConstTextIterator endPrintedText() const;
  CTextIterator endPrintedText();
  CConstFullTextIterator endFullText() const;
  CFullTextIterator endFullText();

  void setMistakeInformation();

  class CFullTextProxy {
    friend class CTextDataTreeImpl;

  public:
    using iterator = CFullTextIterator;
    using const_iterator = CConstFullTextIterator;

    CFullTextIterator begin();
    CConstFullTextIterator begin() const;
    CConstFullTextIterator cbegin() const;

    CFullTextIterator end();
    CConstFullTextIterator end() const;
    CConstFullTextIterator cend() const;

    CIndex size() const;
    bool empty() const;

  private:
    CFullTextProxy(CTextDataTreeImpl* pTree);
    CTextDataTreeImpl* pTree_;
  };

  class CConstFullTextProxy {
    friend class CTextDataTreeImpl;

  public:
    using const_iterator = CConstFullTextIterator;

    CConstFullTextIterator begin() const;
    CConstFullTextIterator cbegin() const;

    CConstFullTextIterator end() const;
    CConstFullTextIterator cend() const;

    CIndex size() const;
    bool empty() const;

  private:
    CConstFullTextProxy(const CTextDataTreeImpl* pTree);
    const CTextDataTreeImpl* pTree_;
  };

  CFullTextProxy textFullView();
  CConstFullTextProxy textConstFullView() const;

  class CPrintedTextProxy {
    friend class CTextDataTreeImpl;

  public:
    using iterator = CTextIterator;
    using const_iterator = CConstTextIterator;

    CTextIterator begin();
    CConstTextIterator begin() const;
    CConstTextIterator cbegin() const;

    CTextIterator end();
    CConstTextIterator end() const;
    CConstTextIterator cend() const;

    CIndex size() const;
    bool empty() const;

  private:
    CPrintedTextProxy(CTextDataTreeImpl* pTree);
    CTextDataTreeImpl* pTree_;
  };

  class CConstPrintedTextProxy {
    friend class CTextDataTreeImpl;

  public:
    using const_iterator = CConstTextIterator;

    CConstTextIterator begin() const;
    CConstTextIterator cbegin() const;

    CConstTextIterator end() const;
    CConstTextIterator cend() const;

    CIndex size() const;
    bool empty() const;

  private:
    CConstPrintedTextProxy(const CTextDataTreeImpl* pTree);
    const CTextDataTreeImpl* pTree_;
  };

  CPrintedTextProxy textPrintedView();
  CConstPrintedTextProxy textConstPrintedView() const;

private:
  void setMistakeRoutes();
  void setMistakeSymbols();
  void setRequiredDeleted();
  void setNodeDepths();

  void reAssignMistakeRoutes(const CTextIterator& currentPosition);
  void assignNewMistakeRoutes(const CTextIterator& currentPosition);
  void assignMistakeRoutesForFinalElement();

  void reAssignChildernTo(const CTextIterator& source, CTextIterator* target);
  void setRequiredDeletedFrom(const CSiblingIterator& currentNode);

  void deleteLastTextDelimiterBlock();
  void deleteLastSymbolBlock();

  CTree Tree_;
  CTextIterator FinalElement_ = rootIterator();
};
using CMistakeRoutesContainer = std::list<CTextDataTreeImpl::CFullTextIterator>;
} // namespace NSTextDataTreeDetail

class CTextNode {
  using CMistakeRoutesContainer = NSTextDataTreeDetail::CMistakeRoutesContainer;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyPosEnum = NSKeyboard::CKeyPosEnum;

public:
  using CIndex = int64_t;
  using CMistakeIterator = CMistakeRoutesContainer::iterator;
  using CConstMistakeIterator = CMistakeRoutesContainer::const_iterator;

  using CTree = NSLibrary::CVTree<CTextNode>;
  using CFullTextIterator = CTree::CPreOrderIterator;

  CTextNode() = default;

  // Default status = ESymbolStatus::TextSymbol
  explicit CTextNode(QChar Symbol, CTime PressingTime, CTime ReleaseTime,
                     ESymbolStatus Status, CKeyPosition Position,
                     CTime ResponseTime);

  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  CTime getResponseTime() const;
  CTime getDurationTime() const;

  QChar getSymbol() const;
  ESymbolStatus getSymbolStatus() const;
  unsigned char getDepth() const;
  void setSymbolStatus(ESymbolStatus newStatus);

  void setDepth(unsigned char Depth);

  void clearMistakeRoutes();

  template<class TOut>
  friend TOut& operator<<(TOut& out, const CTextNode& data) {
    out << data.SymbolStatus_;
    return out;
  }

  CMistakeIterator beginMistakes();
  CConstMistakeIterator beginMistakes() const;
  CConstMistakeIterator cbeginMistakes() const;
  CMistakeIterator endMistakes();
  CConstMistakeIterator endMistakes() const;
  CConstMistakeIterator cendMistakes() const;

  CMistakeIterator eraseMistakeNode(CConstMistakeIterator Current);

  bool hasNoMistakeRoutes() const;
  void addMistakeRoute(CFullTextIterator iter);
  CIndex numberOfMistakeRoutes() const;
  CKeyPosition getPosition() const;

private:
  CTime PressingTime_;
  CTime ReleaseTime_;
  CTime ResponseTime_;
  QChar Symbol_;
  unsigned char Depth_ = 0;
  ESymbolStatus SymbolStatus_ = ESymbolStatus::TextSymbol;
  CKeyPosition KeyPosition_ = CKeyPosEnum::UNKN;
  CMistakeRoutesContainer MistakeRoutes_;
};

class CTextDataTree
    : public NSLibrary::CBasicWrapper<NSTextDataTreeDetail::CTextDataTreeImpl> {
  using CTextDataTreeImpl = NSTextDataTreeDetail::CTextDataTreeImpl;
  using CBase = NSLibrary::CBasicWrapper<CTextDataTreeImpl>;

public:
  using CConstFullTextIterator =
      typename CTextDataTreeImpl::CConstFullTextIterator;
  using CFullTextIterator = typename CTextDataTreeImpl::CFullTextIterator;
  using CConstTextIterator = typename CTextDataTreeImpl::CConstTextIterator;
  using CTextIterator = typename CTextDataTreeImpl::CTextIterator;
  using CConstSiblingIterator =
      typename CTextDataTreeImpl::CConstSiblingIterator;
  using CSiblingIterator = typename CTextDataTreeImpl::CSiblingIterator;

  using CBase::CBase;
};
} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTDATATREE_H
