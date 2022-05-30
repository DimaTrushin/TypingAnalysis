#include "ModifierDataSequencer.h"

namespace NSApplication {
namespace NSKernel {

bool CModifierNonSequencer::isValid() const {
  return false;
}

void CModifierNonSequencer::next() {
}

EKeyStatus CModifierNonSequencer::getStatus() const {
  return EKeyStatus::End;
}

unsigned char CModifierNonSequencer::getDepth() const {
  return 0;
}

CStatusData CModifierNonSequencer::getStatusData() const {
  return {getStatus(), getDepth()};
}

QChar CModifierNonSequencer::getSymbol() const {
  return QChar();
}

CTime CModifierNonSequencer::getTime() const {
  return CTime();
}

CModifierEssentialSequencer::CModifierEssentialSequencer(const CIterator& begin,
                                                         const CIterator& end,
                                                         ETextMode mode)
    : Current_(begin), End_(end), Mode_(mode) {
  while (Current_ != End_ && getDepth() == 0)
    ++Current_;
}

bool CModifierEssentialSequencer::isValid() const {
  return Current_ != End_;
}

void CModifierEssentialSequencer::next() {
  ++Current_;
  while (Current_ != End_ && getDepth() == 0)
    ++Current_;
}

EKeyStatus CModifierEssentialSequencer::getStatus() const {
  if (!isValid())
    return EKeyStatus::End;
  return EKeyStatus::Control;
}

unsigned char CModifierEssentialSequencer::getDepth() const {
  return Current_->getDependencies(Mode_);
}

CStatusData CModifierEssentialSequencer::getStatusData() const {
  return {getStatus(), getDepth()};
}

QChar CModifierEssentialSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CModifierEssentialSequencer::getTime() const {
  return Current_->getPressingTime();
}

CModifierAllSequencer::CModifierAllSequencer(const CIterator& begin,
                                             const CIterator& end,
                                             ETextMode mode)
    : Current_(begin), End_(end), Mode_(mode) {
}

bool CModifierAllSequencer::isValid() const {
  return Current_ != End_;
}

void CModifierAllSequencer::next() {
  ++Current_;
}

EKeyStatus CModifierAllSequencer::getStatus() const {
  if (!isValid())
    return EKeyStatus::End;
  return EKeyStatus::Control;
}

unsigned char CModifierAllSequencer::getDepth() const {
  return Current_->getDependencies(Mode_);
}

CStatusData CModifierAllSequencer::getStatusData() const {
  return {getStatus(), getDepth()};
}

QChar CModifierAllSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CModifierAllSequencer::getTime() const {
  return Current_->getPressingTime();
}

} // namespace NSKernel
} // namespace NSApplication
