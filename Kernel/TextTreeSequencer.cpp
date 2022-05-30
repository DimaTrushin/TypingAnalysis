#include "TextTreeSequencer.h"

namespace NSApplication {
namespace NSKernel {

CTextTreeFullSequencer::CTextTreeFullSequencer(const CIterator& begin,
                                               const CIterator& end)
    : Current_(begin), End_(end) {
}

bool CTextTreeFullSequencer::isValid() const {
  return Current_ != End_;
}

void CTextTreeFullSequencer::next() {
  ++Current_;
}

EKeyStatus CTextTreeFullSequencer::getStatus() const {
  if (!isValid())
    return EKeyStatus::End;
  switch (Current_->getSymbolStatus()) {
  case ESymbolStatus::TextSymbol:
    return EKeyStatus::MainText;
  case ESymbolStatus::DeletedSymbolAccidental:
    return EKeyStatus::AccidentallyDeleted;
  case ESymbolStatus::DeletedSymbolRequired:
    return EKeyStatus::RequiredDeletion;
  case ESymbolStatus::ErroneousSymbol:
    return EKeyStatus::Erroneous;
  default:
    assert(false);
    return EKeyStatus::Ignore;
  }
}

unsigned char CTextTreeFullSequencer::getDepth() const {
  return Current_->getDepth();
}

CStatusData CTextTreeFullSequencer::getStatusData() const {
  return {getStatus(), getDepth()};
}

CTextTreeFullSequencer::CKeyPosition
CTextTreeFullSequencer::getPosition() const {
  return Current_->getPosition();
}

QChar CTextTreeFullSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CTextTreeFullSequencer::getPressingTime() const {
  return Current_->getPressingTime();
}

CTime CTextTreeFullSequencer::getReleasingTime() const {
  return Current_->getReleasingTime();
}

bool CTextTreeFullSequencer::isAutoRepeat() const {
  return Current_->isAutoRepeat();
}

CTextTreePrintedSequencer::CTextTreePrintedSequencer(const CIterator& begin,
                                                     const CIterator& end)
    : Current_(begin), End_(end) {
}

bool CTextTreePrintedSequencer::isValid() const {
  return Current_ != End_;
}

void CTextTreePrintedSequencer::next() {
  ++Current_;
}

EKeyStatus CTextTreePrintedSequencer::getStatus() const {
  if (!isValid())
    return EKeyStatus::End;
  switch (Current_->getSymbolStatus()) {
  case ESymbolStatus::TextSymbol:
    return EKeyStatus::MainText;
  case ESymbolStatus::DeletedSymbolAccidental:
    return EKeyStatus::AccidentallyDeleted;
  case ESymbolStatus::DeletedSymbolRequired:
    return EKeyStatus::RequiredDeletion;
  case ESymbolStatus::ErroneousSymbol:
    return EKeyStatus::Erroneous;
  default:
    assert(false);
    return EKeyStatus::Ignore;
  }
}

unsigned char CTextTreePrintedSequencer::getDepth() const {
  return Current_->getDepth();
}

CStatusData CTextTreePrintedSequencer::getStatusData() const {
  return {getStatus(), getDepth()};
}

CTextTreePrintedSequencer::CKeyPosition
CTextTreePrintedSequencer::getPosition() const {
  return Current_->getPosition();
}

QChar CTextTreePrintedSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CTextTreePrintedSequencer::getPressingTime() const {
  return Current_->getPressingTime();
}

CTime CTextTreePrintedSequencer::getReleasingTime() const {
  return Current_->getReleasingTime();
}

bool CTextTreePrintedSequencer::isAutoRepeat() const {
  return Current_->isAutoRepeat();
}

} // namespace NSKernel
} // namespace NSApplication
