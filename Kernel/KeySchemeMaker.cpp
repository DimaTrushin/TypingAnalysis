#include "KeySchemeMaker.h"

namespace NSApplication {
namespace NSKernel {
namespace NSKeySchemeMakerDetail {

bool CKeySegmentBuilt::CFirstReleasedOnTop::operator()(
    const CKeySegmentBuilt& first, const CKeySegmentBuilt& second) {
  return first.ReleasingTime > second.ReleasingTime;
}

template<class TIterator>
QString CKeySegmentsUnderConstruction::getKeyText(TIterator iter) {
  return iter->getSymbol();
}

template<>
QString CKeySegmentsUnderConstruction::getKeyText<CSession::const_iterator>(
    CSession::const_iterator iter) {
  return iter->getRawSymbol();
}

CKeySegmentsUnderConstruction::CKeyPosition
CKeySegmentsUnderConstruction::getTopPosition() const {
  return KeysBuilt_.top().KeyPosition;
}

CTime CKeySegmentsUnderConstruction::getFirstReleaseTime() const {
  if (empty())
    return CTime();
  return KeysBuilt_.top().ReleasingTime;
}

bool CKeySegmentsUnderConstruction::empty() const {
  return KeysBuilt_.empty();
}

CKeySegmentsUnderConstruction::CIndex
CKeySegmentsUnderConstruction::size() const {
  return KeysBuilt_.size();
}

CKeySegmentBuilt CKeySegmentsUnderConstruction::getAndRelease() {
  assert(!empty());
  updateMultiplicities(KeysBuilt_.top().ReleasingTime);
  CKeySegmentBuilt Key(std::move(KeysBuilt_.top()));
  KeysBuilt_.pop();
  return Key;
}

template<class TSequencer>
void CKeySegmentsUnderConstruction::insertKey(const TSequencer& Sequencer,
                                              CTime BeginTime) {
  auto iterKey = std::find_if(
      KeysBuilt_.begin(), KeysBuilt_.end(),
      [Position = Sequencer.getPosition()](const CKeySegmentBuilt& Segment) {
        return Segment.KeyPosition == Position;
      });
  if (iterKey == KeysBuilt_.end()) {
    updateMultiplicities(Sequencer.getPressingTime() - BeginTime);
    KeysBuilt_.push({CKeySegment(Sequencer.getSymbol(),
                                 Sequencer.getPressingTime() - BeginTime),
                     Sequencer.getReleasingTime() - BeginTime,
                     Sequencer.getPosition()});
  } else {
    iterKey->Segment.addText(Sequencer.getSymbol());
  }
}

void CKeySegmentsUnderConstruction::updateMultiplicities(CTime NewKeyTime) {
  for (auto& KeyBuilt : KeysBuilt_)
    KeyBuilt.Segment.AddSegment(size(), NewKeyTime);
}

} // namespace NSKeySchemeMakerDetail

CKeyScheme CKeySchemeMaker::make(const CTextData& TextData,
                                 const CFingerLayout& Layout) {
  switch (TextData.textMode()) {
  case ETextMode::Raw:
    return makeScheme(TextData.sessionSequencer(), Layout);
  case ETextMode::Full:
    return makeScheme(TextData.fullTextSequencer(), Layout);
  case ETextMode::Printed:
    return makeScheme(TextData.printedTextSequencer(), Layout);
  default:
    assert(false);
    return {};
  }
}

template<class TSequencer>
CKeyScheme CKeySchemeMaker::makeScheme(TSequencer Sequencer,
                                       const CFingerLayout& Layout) {
  if (!Sequencer.isValid())
    return {};
  CKeyScheme KeyScheme = CKeyScheme::getDefaultEmpty();
  BeginTime_ = Sequencer.getPressingTime();

  while (!isWorkDone(Sequencer)) {
    if (isPressingNext(Sequencer)) {
      handlePressing(&Sequencer);
    } else {
      handleReleasing(Layout, &KeyScheme);
    }
  }
  return KeyScheme;
}

template<class TSequencer>
bool CKeySchemeMaker::isWorkDone(const TSequencer& Sequencer) const {
  return !Sequencer.isValid() && KeysSegmentsBuilt_.empty();
}

template<class TSequencer>
bool CKeySchemeMaker::isPressingNext(const TSequencer& Sequencer) const {
  if (!Sequencer.isValid())
    return false;
  if (KeysSegmentsBuilt_.empty())
    return true;
  return Sequencer.getPressingTime() - BeginTime_ <
         KeysSegmentsBuilt_.getFirstReleaseTime();
}

template<class TSequencer>
void CKeySchemeMaker::handlePressing(TSequencer* pSequencer) {
  KeysSegmentsBuilt_.insertKey(*pSequencer, BeginTime_);
  pSequencer->next();
}

void CKeySchemeMaker::handleReleasing(const CFingerLayout& Layout,
                                      CKeyScheme* pKeyScheme) {
  CFinger KeyFinger = Layout.find(KeysSegmentsBuilt_.getTopPosition());
  pKeyScheme->add(KeyFinger, KeysSegmentsBuilt_.getAndRelease().Segment);
}

} // namespace NSKernel
} // namespace NSApplication
