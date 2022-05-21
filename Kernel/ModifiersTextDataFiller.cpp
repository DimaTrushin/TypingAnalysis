#include "ModifiersTextDataFiller.h"

namespace NSApplication {
namespace NSKernel {
namespace NSModifiersTextDataFillerDetails {

bool CPressedModifiers::CFirstRelease::operator()(
    const CModifierData::iterator& lhs,
    const CModifierData::iterator& rhs) const {
  return lhs->getReleasingTime() > rhs->getReleasingTime();
}

void CPressedModifiers::pressKey(CModifierData::iterator it) {
  PressedKeys_.push(it);
}

void CPressedModifiers::increaseDependencies(ETextMode mode) {
  for (auto& key : PressedKeys_) {
    key->increaseDependencies(mode, 1);
  }
}

void CPressedModifiers::releaseBefore(CTime Time) {
  while (!PressedKeys_.empty() && PressedKeys_.top()->getReleasingTime() < Time)
    PressedKeys_.pop();
}

void CPressedModifiers::clear() {
  PressedKeys_.clear();
}

bool CPressedModifiers::empty() const {
  return PressedKeys_.empty();
}

} // namespace NSModifiersTextDataFillerDetails

void CModifiersTextDataFiller::fill(const CSession& Session,
                                    const CTextDataTree& TextTree,
                                    CModifiersTextData* pData) {
  assert(pData);
  fillShifts(Session, TextTree, &pData->Shifts);
  fillCtrls(Session, TextTree, &pData->Ctrls);
  fillAlts(Session, TextTree, &pData->Alts);
}

void CModifiersTextDataFiller::fillDependencies(const CTextDataTree& TextTree,
                                                CModifierData* pData) {
  assert(pData);
  PressedModifiers_.clear();
  auto it = pData->begin();
  auto itFull = TextTree->beginFullText();
  while (it != pData->end() && itFull != TextTree->endFullText()) {
    if (itFull->getPressingTime() < it->getPressingTime()) {
      PressedModifiers_.releaseBefore(itFull->getPressingTime());
      PressedModifiers_.increaseDependencies(ETextMode::Full);
      if (itFull->getSymbolStatus() == ESymbolStatus::TextSymbol ||
          itFull->getSymbolStatus() == ESymbolStatus::ErroneousSymbol)
        PressedModifiers_.increaseDependencies(ETextMode::Printed);
      ++itFull;
    } else {
      PressedModifiers_.pressKey(it);
      ++it;
    }
  }
  while (!PressedModifiers_.empty() && itFull != TextTree->endFullText()) {
    PressedModifiers_.releaseBefore(itFull->getPressingTime());
    PressedModifiers_.increaseDependencies(ETextMode::Full);
    if (itFull->getSymbolStatus() == ESymbolStatus::TextSymbol ||
        itFull->getSymbolStatus() == ESymbolStatus::ErroneousSymbol)
      PressedModifiers_.increaseDependencies(ETextMode::Printed);
    ++itFull;
  }
}

void CModifiersTextDataFiller::fillShifts(const CSession& Session,
                                          const CTextDataTree& TextTree,
                                          CModifierData* pData) {
  assert(pData);
  findShifts(Session, pData);
  fillDependencies(TextTree, pData);
}

void CModifiersTextDataFiller::fillCtrls(const CSession& Session,
                                         const CTextDataTree& TextTree,
                                         CModifierData* pData) {
  assert(pData);
  findCtrls(Session, pData);
  fillDependencies(TextTree, pData);
}

void CModifiersTextDataFiller::fillAlts(const CSession& Session,
                                        const CTextDataTree& TextTree,
                                        CModifierData* pData) {
  assert(pData);
  findAlts(Session, pData);
  fillDependencies(TextTree, pData);
}

void CModifiersTextDataFiller::findShifts(const CSession& Session,
                                          CModifierData* pData) {
  assert(pData);
  pData->clear();
  for (const auto& key : Session) {
    if (key.isShift())
      pData->push_back(CModifierDatum(key));
  }
}

void CModifiersTextDataFiller::findCtrls(const CSession& Session,
                                         CModifierData* pData) {
  assert(pData);
  pData->clear();
  for (const auto& key : Session) {
    if (key.isCtrl())
      pData->push_back(CModifierDatum(key));
  }
}

void CModifiersTextDataFiller::findAlts(const CSession& Session,
                                        CModifierData* pData) {
  assert(pData);
  pData->clear();
  for (const auto& key : Session) {
    if (key.isAlt())
      pData->push_back(CModifierDatum(key));
  }
}

} // namespace NSKernel
} // namespace NSApplication
