#ifndef NSAPPLICATION_NSKERNEL_CTEXTTREESEQUENCER_H
#define NSAPPLICATION_NSKERNEL_CTEXTTREESEQUENCER_H

#include "KeyStatus.h"
#include "Keyboard/KeyPosition.h"
#include "TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

class CTextTreeFullSequencer {
  using CIterator = CTextDataTree::CConstFullTextIterator;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  CTextTreeFullSequencer(const CIterator& begin, const CIterator& end);
  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  CKeyPosition getPosition() const;
  QChar getSymbol() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  bool isAutoRepeat() const;

private:
  CIterator Current_;
  CIterator End_;
};

class CTextTreePrintedSequencer {
  using CIterator = CTextDataTree::CConstTextIterator;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  CTextTreePrintedSequencer(const CIterator& begin, const CIterator& end);
  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  CKeyPosition getPosition() const;
  QChar getSymbol() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  bool isAutoRepeat() const;

private:
  CIterator Current_;
  CIterator End_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTTREESEQUENCER_H
