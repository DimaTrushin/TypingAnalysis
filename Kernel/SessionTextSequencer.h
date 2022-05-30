#ifndef NSAPPLICATION_NSKERNEL_CSESSIONTEXTSEQUENCER_H
#define NSAPPLICATION_NSKERNEL_CSESSIONTEXTSEQUENCER_H

#include "KeyStatus.h"
#include "Keyboard/KeyPosition.h"
#include "Session.h"

namespace NSApplication {
namespace NSKernel {

class CSessionTextSequencer {
  using CIterator = CSession::const_iterator;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  CSessionTextSequencer(const CIterator& begin, const CIterator& end);
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

#endif // NSAPPLICATION_NSKERNEL_CSESSIONTEXTSEQUENCER_H
