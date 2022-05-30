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
  return EKeyStatus::Ignore;
}

unsigned char CSessionTextSequencer::getDepth() const {
  return 0;
}

CStatusData CSessionTextSequencer::getStatusData() const {
  return {getStatus(), getDepth()};
}

QChar CSessionTextSequencer::getSymbol() const {
  switch (getStatus()) {
  case EKeyStatus::MainText:
    return Current_->getLastSymbol();
  case EKeyStatus::Backspace:
  case EKeyStatus::Control:
  case EKeyStatus::SilentDeadKey:
    return Current_->getLabel().LowSymbol;
  default:
    return QChar();
  }
}

} // namespace NSKernel
} // namespace NSApplication
