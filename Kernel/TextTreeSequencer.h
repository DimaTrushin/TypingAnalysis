#ifndef NSAPPLICATION_NSKERNEL_CTEXTTREESEQUENCER_H
#define NSAPPLICATION_NSKERNEL_CTEXTTREESEQUENCER_H

#include "KeyStatus.h"
#include "TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

class CTextTreeFullSequencer {
  using CIterator = CTextDataTree::CConstFullTextIterator;

public:
  CTextTreeFullSequencer(const CIterator& begin, const CIterator& end);
  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  QChar getSymbol() const;
  CTime getPressingTime() const;
  bool isAutoRepeat() const;

private:
  CIterator Current_;
  CIterator End_;
};

class CTextTreePrintedSequencer {
  using CIterator = CTextDataTree::CConstTextIterator;

public:
  CTextTreePrintedSequencer(const CIterator& begin, const CIterator& end);
  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  QChar getSymbol() const;
  CTime getPressingTime() const;
  bool isAutoRepeat() const;

private:
  CIterator Current_;
  CIterator End_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTTREESEQUENCER_H
