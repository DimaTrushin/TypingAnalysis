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

CModifierNonSequencer::CKeyPosition CModifierNonSequencer::getPosition() const {
  return NSKeyboard::CKeyPosEnum::IGNR;
}

QChar CModifierNonSequencer::getSymbol() const {
  return QChar();
}

CTime CModifierNonSequencer::getPressingTime() const {
  return CTime();
}

CTime CModifierNonSequencer::getReleasingTime() const {
  return CTime();
}

bool CModifierNonSequencer::isAutoRepeat() const {
  return false;
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

CModifierEssentialSequencer::CKeyPosition
CModifierEssentialSequencer::getPosition() const {
  return Current_->getPosition();
}

QChar CModifierEssentialSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CModifierEssentialSequencer::getPressingTime() const {
  return Current_->getPressingTime();
}

CTime CModifierEssentialSequencer::getReleasingTime() const {
  return Current_->getReleasingTime();
}

bool CModifierEssentialSequencer::isAutoRepeat() const {
  return Current_->isAutoRepeat();
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

CModifierAllSequencer::CKeyPosition CModifierAllSequencer::getPosition() const {
  return Current_->getPosition();
}

QChar CModifierAllSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CModifierAllSequencer::getPressingTime() const {
  return Current_->getPressingTime();
}

CTime CModifierAllSequencer::getReleasingTime() const {
  return Current_->getReleasingTime();
}

bool CModifierAllSequencer::isAutoRepeat() const {
  return Current_->isAutoRepeat();
}

} // namespace NSKernel
} // namespace NSApplication
