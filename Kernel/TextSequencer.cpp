#include "TextSequencer.h"

#include "ModifierDataSequencer.h"
#include "TextTreeSequencer.h"

namespace NSApplication {
namespace NSKernel {
namespace NSTextSequencerDetail {
bool CTextSequencerBase::isValid() const {
  return !Sequencers_.empty();
}

void CTextSequencerBase::next() {
  CUniversalTextSequencer Sequencer = Sequencers_.extract();
  Sequencer->next();
  if (Sequencer->isValid())
    Sequencers_.push(std::move(Sequencer));
}

EKeyStatus CTextSequencerBase::getStatus() const {
  if (!isValid())
    return EKeyStatus::End;
  return Sequencers_.top()->getStatus();
}

unsigned char CTextSequencerBase::getDepth() const {
  if (!isValid())
    return 0;
  return Sequencers_.top()->getDepth();
}

CStatusData CTextSequencerBase::getStatusData() const {
  return {getStatus(), getDepth()};
}

CTextSequencerBase::CKeyPosition CTextSequencerBase::getPosition() const {
  if (!isValid())
    return NSKeyboard::CKeyPosEnum::IGNR;
  return Sequencers_.top()->getPosition();
}

QChar CTextSequencerBase::getSymbol() const {
  if (!isValid())
    return QChar();
  return Sequencers_.top()->getSymbol();
}

CTime CTextSequencerBase::getPressingTime() const {
  if (!isValid())
    return CTime();
  return Sequencers_.top()->getPressingTime();
}

CTime CTextSequencerBase::getReleasingTime() const {
  if (!isValid())
    return CTime();
  return Sequencers_.top()->getReleasingTime();
}

bool CTextSequencerBase::isAutoRepeat() const {
  if (!isValid())
    return false;
  return Sequencers_.top()->isAutoRepeat();
}
} // namespace NSTextSequencerDetail

CFullTextSequencer::CFullTextSequencer(const CTextDataTree& TextTree,
                                       const CModifiersTextData& Modifiers,
                                       CTextMode mode)
    : CBase(CTextTreeFullSequencer(TextTree->beginFullText(),
                                   TextTree->endFullText())) {
  AddModifier(Modifiers.Shifts, mode.ShiftMode);
  AddModifier(Modifiers.Ctrls, mode.CtrlMode);
  AddModifier(Modifiers.Alts, mode.AltMode);
}

void CFullTextSequencer::AddModifier(const CModifierData& Modifier,
                                     EModifierMode mode) {
  switch (mode) {
  case EModifierMode::All:
    CBase::push(CModifierAllSequencer(Modifier.begin(), Modifier.end(),
                                      ETextMode::Full));
    break;
  case EModifierMode::Essential:
    CBase::push(CModifierEssentialSequencer(Modifier.begin(), Modifier.end(),
                                            ETextMode::Full));
    break;
  default:
    break;
  }
}

CPrintedTextSequencer::CPrintedTextSequencer(
    const CTextDataTree& TextTree, const CModifiersTextData& Modifiers,
    CTextMode mode)
    : CBase(CTextTreePrintedSequencer(TextTree->beginPrintedText(),
                                      TextTree->endPrintedText())) {
  AddModifier(Modifiers.Shifts, mode.ShiftMode);
  AddModifier(Modifiers.Ctrls, mode.CtrlMode);
  AddModifier(Modifiers.Alts, mode.AltMode);
}

void CPrintedTextSequencer::AddModifier(const CModifierData& Modifier,
                                        EModifierMode mode) {
  switch (mode) {
  case EModifierMode::All:
    CBase::push(CModifierAllSequencer(Modifier.begin(), Modifier.end(),
                                      ETextMode::Printed));
    break;
  case EModifierMode::Essential:
    CBase::push(CModifierEssentialSequencer(Modifier.begin(), Modifier.end(),
                                            ETextMode::Printed));
    break;
  default:
    break;
  }
}

// namespace NSTextSequencerDetail

} // namespace NSKernel
} // namespace NSApplication
