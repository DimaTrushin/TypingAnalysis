#ifndef NSAPPLICATION_NSKERNEL_CTEXTDATATREE_H
#define NSAPPLICATION_NSKERNEL_CTEXTDATATREE_H

#include "Library/StlExtension/MvcWrappers.h"
#include "TextMode.h"
#include "TimeApp.h"
#include "VTree.h"

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

class CTextNode {
public:
  using TreePtr = NSLibrary::CVTree<CTextNode>*;
  // struct Handler {pHost, index};
  // using CMistakeRoutesContainer = std::list<Handler>;
  using CIndex = int64_t;

  // Root node is created by default
  CTextNode() = default;

  // pressing time, releasing time, response time
  // Default status = ESymbolStatus::TextSymbol
  explicit CTextNode(QChar Symbol, ESymbolStatus Status);

  //  bool isTextDelimiter() const;
  //  bool isSymbol() const;
  //  bool isAnyDeleted() const;
  //  bool isAnyPrinted() const;

  //  CTime getPressingTime() const;
  //  CTime getReleasingTime() const;
  //  CTime getResponseTime() const;
  //  CTime getDurationTime() const;

  QChar getSymbol() const;
  ESymbolStatus getSymbolStatus() const;
  void setSymbolStatus(ESymbolStatus newStatus);

  template<class TOut>
  friend TOut& operator<<(TOut& out, const CTextNode& data) {
    out << data.SymbolStatus_;
    return out;
  }

private:
  //  CTime ResponseTime_;
  //  CTime PressingTime_;
  //  CTime ReleaseTime_;
  QChar Symbol_;
  ESymbolStatus SymbolStatus_ = ESymbolStatus::TextSymbol;
};

namespace NSTextDataTreeDetail {

// The TextDataTree always has a root
class CTextDataTreeImpl {
public:
  using CTree = NSLibrary::CVTree<CTextNode>;
  using CIndex = CTextNode::CIndex;

  using CConstFullTextIterator = CTree::CConstPreOrderIterator;
  using CFullTextIterator = CTree::CPreOrderIterator;
  using CConstTextIterator = CTree::CConstLastSonIterator;
  using CTextIterator = CTree::CLastSonIterator;

  // These two iterators do not have a travel logic
  // They denote the begin and the end of a text
  // with a chosen TextMode
  using CConstBasicIterator = CTree::CConstBasicIterator;
  using CBasicIterator = CTree::CBasicIterator;

  CTextDataTreeImpl() = default;
  CTextDataTreeImpl(const CTextDataTreeImpl&) = delete;
  CTextDataTreeImpl(CTextDataTreeImpl&&) noexcept = delete;
  CTextDataTreeImpl& operator=(const CTextDataTreeImpl&) = delete;
  CTextDataTreeImpl& operator=(CTextDataTreeImpl&&) noexcept = delete;

  void clear();
  void add(QChar Symbol, ESymbolStatus Status);
  void addData(const CTextNode& TextData);
  void addData(CTextNode&& TextData);
  // action for Backspace
  void deleteLastData();
  // action for Ctrl + Backspace
  //  void deleteLastBlock();

  CIndex getNumberOfPlacesWithDeletion() const;
  CIndex getNumberOfDeletionSeries() const;
  CIndex getNumberOfDeletedSymbols() const;
  // The number of times text deleting begins
  CIndex getNumberOfReturnPoints() const;
  //  // including the root symbol
  CIndex getTotalNumberOfSymbols() const;

  //  CIndex getTextLength(ETextMode TextMode) const;
  //  CIndex getDeletionSeriesLengthSupremum() const;
  //  CIndex getNumberOfMistakePlaces() const;
  //  CIndex getNumberOfMistakeRoutes() const;
  //  CIndex getMistakeRoutesLengthSupremum() const;

  //  bool isTextEmpty(ETextMode TextMode) const;
  //  microseconds getFirstPressingTime(ETextMode TextMode) const;
  //  microseconds getLastPressingTime(ETextMode TextMode) const;
  //  microseconds getTextDurationTime(ETextMode TextMode) const;

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

private:
  //  void setFinalElement(const CTextDataTree& Tree);
  //  void setFinalElementHost();

  //  CIndex getPrintedTextLength() const;
  //  CIndex getFullTextLength() const;

  //  void deleteLastTextDelimiterBlock();
  //  void deleteLastSymbolBlock();

  CTree Tree_{CTextNode(QChar(), ESymbolStatus::RootSymbol)};
  CTextIterator FinalElement_ = rootIterator();
};
} // namespace NSTextDataTreeDetail

using CTextDataTree =
    NSLibrary::CBasicWrapper<NSTextDataTreeDetail::CTextDataTreeImpl>;
} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTDATATREE_H
