#include "SessionTextSequencer.h"

namespace NSApplication {
namespace NSKernel {

CSessionTextSequencer::CSessionTextSequencer(const CIterator& begin,
                                             const CIterator& end)
    : Current_(begin), End_(end) {
}

bool CSessionTextSequencer::isValid() const {
  return Current_ != End_;
}

void CSessionTextSequencer::next() {
  ++Current_;
}

EKeyStatus CSessionTextSequencer::getStatus() const {
  if (!isValid())
    return EKeyStatus::End;
  if (Current_->isBackspace())
    return EKeyStatus::Backspace;
  if (Current_->isTrackableSpecial())
    return EKeyStatus::Control;
  if (Current_->isSilentDeadKey())
    return EKeyStatus::SilentDeadKey;
  if (Current_->getTextSize() > 0)
    return EKeyStatus::MainText;
  if (Current_->getLabel().Size > 0)
    return EKeyStatus::Control;
  return EKeyStatus::Ignore;
}

unsigned char CSessionTextSequencer::getDepth() const {
  return 0;
}

CStatusData CSessionTextSequencer::getStatusData() const {
  return {getStatus(), getDepth()};
}

CSessionTextSequencer::CKeyPosition CSessionTextSequencer::getPosition() const {
  return Current_->getPosition();
}

QChar CSessionTextSequencer::getSymbol() const {
  return Current_->getRawSymbol();
}

CTime CSessionTextSequencer::getPressingTime() const {
  return Current_->getPressingTime();
}

CTime CSessionTextSequencer::getReleasingTime() const {
  return Current_->getReleasingTime();
}

bool CSessionTextSequencer::isAutoRepeat() const {
  return Current_->isAutoRepeat();
}

} // namespace NSKernel
} // namespace NSApplication
