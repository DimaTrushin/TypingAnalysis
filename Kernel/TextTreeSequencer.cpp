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

QChar CTextTreeFullSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CTextTreeFullSequencer::getTime() const {
  return Current_->getPressingTime();
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

QChar CTextTreePrintedSequencer::getSymbol() const {
  return Current_->getSymbol();
}

CTime CTextTreePrintedSequencer::getTime() const {
  return Current_->getPressingTime();
}

} // namespace NSKernel
} // namespace NSApplication
