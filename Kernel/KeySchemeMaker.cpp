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
  // TO DO
  // prelimenary implementation
  return iter->getSymbol();
}

template<>
QString CKeySegmentsUnderConstruction::getKeyText<CSession::const_iterator>(
    CSession::const_iterator iter) {
  // TO DO
  // prelimenary implementation
  if (iter->isTrackableSpecial() || iter->isSilentDeadKey()) {
    return iter->getLabel().LowSymbol;
  } else if (iter->getTextSize() > 0) {
    return iter->getLastSymbol();
  } else if (iter->getLabel().Size > 0) {
    return iter->getLabel().LowSymbol;
  }
  return "";
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

template<class TIterator>
void CKeySegmentsUnderConstruction::insertKey(TIterator iter, CTime BeginTime) {
  auto iterKey = std::find_if(
      KeysBuilt_.begin(), KeysBuilt_.end(),
      [Position = iter->getPosition()](const CKeySegmentBuilt& Segment) {
        return Segment.KeyPosition == Position;
      });
  if (iterKey == KeysBuilt_.end()) {
    updateMultiplicities(iter->getPressingTime() - BeginTime);
    KeysBuilt_.push(
        {CKeySegment(getKeyText(iter), iter->getPressingTime() - BeginTime),
         iter->getReleasingTime() - BeginTime, iter->getPosition()});
  } else {
    iterKey->Segment.addText(getKeyText(iter));
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
    return makeScheme(TextData.rawSession(), Layout);
  case ETextMode::Full:
    return makeScheme(TextData.textConstFullView(), Layout);
  case ETextMode::Printed:
    return makeScheme(TextData.textConstPrintedView(), Layout);
  default:
    assert(false);
    return {};
  }
}

template<class TTextView>
CKeyScheme CKeySchemeMaker::makeScheme(const TTextView& TextView,
                                       const CFingerLayout& Layout) {
  if (TextView.empty())
    return {};
  CKeyScheme KeyScheme = CKeyScheme::getDefaultEmpty();
  auto iter = TextView.cbegin();
  auto sentinel = TextView.cend();
  BeginTime_ = iter->getPressingTime();

  while (!isWorkDone(iter, sentinel)) {
    if (isPressingNext(iter, sentinel)) {
      handlePressing(&iter);
    } else {
      handleReleasing(Layout, &KeyScheme);
    }
  }
  return KeyScheme;
}

template<class TIterator>
bool CKeySchemeMaker::isWorkDone(TIterator iter, TIterator sentinel) const {
  return (iter == sentinel) && KeysSegmentsBuilt_.empty();
}

template<class TIterator>
bool CKeySchemeMaker::isPressingNext(TIterator iter, TIterator sentinel) const {
  if (iter == sentinel)
    return false;
  if (KeysSegmentsBuilt_.empty())
    return true;
  return iter->getPressingTime() - BeginTime_ <
         KeysSegmentsBuilt_.getFirstReleaseTime();
}

template<class TIterator>
void CKeySchemeMaker::handlePressing(TIterator* piter) {
  KeysSegmentsBuilt_.insertKey(*piter, BeginTime_);
  ++(*piter);
}

void CKeySchemeMaker::handleReleasing(const CFingerLayout& Layout,
                                      CKeyScheme* pKeyScheme) {
  CFinger KeyFinger = Layout.find(KeysSegmentsBuilt_.getTopPosition());
  pKeyScheme->add(KeyFinger, KeysSegmentsBuilt_.getAndRelease().Segment);
}

} // namespace NSKernel
} // namespace NSApplication
