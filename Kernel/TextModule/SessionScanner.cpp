#include "SessionScanner.h"

namespace NSApplication {
namespace NSKernel {

namespace NSSessionScanner {

QString* CSessionScanner::run(const CSession& Session, QString* Text) {
  setInternalResourses(Text);
  preallocateText(Session);
  processSession(Session);
  return Text_;
}

void CSessionScanner::processSession(const CSession& Session) {
  for (const CKeyEvent& KeyEvent : Session) {
    processKeyEvent(KeyEvent);
  }
}

void CSessionScanner::processKeyEvent(const CKeyEvent& KeyEvent) {
  for (int Index = 0; Index < getKeyEventSize(KeyEvent); ++Index) {
    Text_->push_back(getSymbol(KeyEvent, Index));
  }
}

QChar CSessionScanner::getSymbol(const CKeyEvent& KeyEvent, int SymbolIndex) {
  assert(SymbolIndex >= 0);
  assert(SymbolIndex < getKeyEventSize(KeyEvent));
  return KeyEvent.getText().Symbol[SymbolIndex];
}

void CSessionScanner::setInternalResourses(QString* Text) {
  assert(Text);
  Text_ = Text;
}

void CSessionScanner::preallocateText(const CSession& Session) {
  Text_->reserve(getSessionTextSize(Session));
}

size_t CSessionScanner::getSessionTextSize(const CSession& Session) {
  size_t TextSize = 0;
  for (const CKeyEvent& KeyEvent : Session) {
    TextSize += getKeyEventSize(KeyEvent);
  }
  return TextSize;
}

size_t CSessionScanner::getKeyEventSize(const CKeyEvent& KeyEvent) {
  return KeyEvent.getText().Size;
}

} // namespace NSSessionScanner

} // namespace NSKernel
} // namespace NSApplication
