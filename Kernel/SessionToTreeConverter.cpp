#include "SessionToTreeConverter.h"

#include "Session.h"
#include "TextDataTree.h"

#include <cassert>

namespace NSApplication {
namespace NSKernel {

void CSessionToTreeConverter::convert(const CSession& Source,
                                      CTextDataTree* pTarget) {
  assert(pTarget);
  CTextDataTree& Target = *pTarget;
  Target->clear();

  if (Source.empty())
    return;

  LastPressedTime_ = Source.begin()->getPressingTime();
  for (const auto& KeyEvent : Source)
    handleEvent_(KeyEvent, pTarget);
  Target->setMistakeInformation();
}

void CSessionToTreeConverter::handleEvent_(const CKeyEvent& KeyEvent,
                                           CTextDataTree* pTarget) {
  CTextDataTree& Target = *pTarget;
  if (KeyEvent.hasText())
    for (unsigned char i = 0; i < KeyEvent.getTextSize(); ++i) {
      Target->add(KeyEvent.getSymbol(i), KeyEvent.getPressingTime(),
                  KeyEvent.getReleasingTime(), ESymbolStatus::TextSymbol,
                  KeyEvent.getPosition(),
                  KeyEvent.getPressingTime() - LastPressedTime_);
      LastPressedTime_ = KeyEvent.getPressingTime();
    }

  if (KeyEvent.isBackspace()) {
    if (KeyEvent.isCtrlActive())
      Target->deleteLastBlock();
    else
      Target->deleteLastData();
  }
  LastPressedTime_ = KeyEvent.getPressingTime();
}

} // namespace NSKernel
} // namespace NSApplication
