#include "KeySchemeMaker.h"

#include <QDebug>

namespace NSApplication {
namespace NSKernel {
namespace NSKeySchemeMakerDetail {

bool CKeySegmentBuilt::CFirstReleasedOnTop::operator()(
    const CKeySegmentBuilt& first, const CKeySegmentBuilt& second) {
  return first.ReleasingTime > second.ReleasingTime;
}

template<class TIterator>
QString CKeysUnderConstruction::getKeyText(TIterator iter) {
  // TO DO
  return "";
}

template<>
QString CKeysUnderConstruction::getKeyText<CSession::const_iterator>(
    CSession::const_iterator iter) {
  // TO DO
  return "";
}

CKeysUnderConstruction::CKeyPosition
CKeysUnderConstruction::getTopPosition() const {
  return KeysBuilt_.top().KeyPosition;
}

CTime CKeysUnderConstruction::getFirstReleaseTime() const {
  if (empty())
    return CTime();
  return KeysBuilt_.top().ReleasingTime;
}

bool CKeysUnderConstruction::empty() const {
  return KeysBuilt_.empty();
}

CKeysUnderConstruction::CIndex CKeysUnderConstruction::size() const {
  return KeysBuilt_.size();
}

CKeySegmentBuilt CKeysUnderConstruction::getAndRelease() {
  assert(!empty());
  updateMultiplicities(KeysBuilt_.top().ReleasingTime);
  CKeySegmentBuilt Key(std::move(KeysBuilt_.top()));
  KeysBuilt_.pop();
  return Key;
}

template<class TIterator>
void CKeysUnderConstruction::insertKey(TIterator iter) {
  auto iterKey = std::find_if(
      KeysBuilt_.begin(), KeysBuilt_.end(),
      [Position = iter->getPosition()](const CKeySegmentBuilt& Segment) {
        return Segment.KeyPosition == Position;
      });
  if (iterKey == KeysBuilt_.end()) {
    updateMultiplicities(iter->getPressingTime());
    KeysBuilt_.push({CKeySegment(getKeyText(iter), iter->getPressingTime()),
                     iter->getReleasingTime(), iter->getPosition()});
  } else {
    iterKey->Segment.addText(getKeyText(iter));
  }
}

void CKeysUnderConstruction::updateMultiplicities(CTime NewKeyTime) {
  for (auto& KeyBuilt : KeysBuilt_)
    KeyBuilt.Segment.AddSegment(size(), NewKeyTime);
}

} // namespace NSKeySchemeMakerDetail

CKeyScheme CKeySchemeMaker::make(const CTextData& TextData,
                                 const CFingerLayout& Layout) {
  switch (TextData.textMode()) {
  case ETextMode::Raw:
    return makeRaw(TextData.rawSession(), Layout);
  case ETextMode::Full:
    return makeText(TextData.textConstFullView(), Layout);
  case ETextMode::Printed:
    return makeText(TextData.textConstPrintedView(), Layout);
  default:
    assert(false);
    return {};
  }
}

CKeyScheme CKeySchemeMaker::makeRaw(const CSession& Session,
                                    const CFingerLayout& Layout) {
  if (Session.empty())
    return {};
  CKeyScheme KeyScheme = CKeyScheme::getDefaultEmpty();
  auto iter = Session.cbegin();
  auto sentinel = Session.cend();

  while (!isWorkDone(iter, sentinel)) {
    if (isPressingNext(iter, sentinel)) {
      handlePressing(&iter);
    } else {
      handleReleasing(Layout, &KeyScheme);
    }
  }
  return KeyScheme;
}

template<class TContainer>
CKeyScheme CKeySchemeMaker::makeText(const TContainer& Container,
                                     const CFingerLayout& Layout) {
  // TO DO
  return {};
}

bool CKeySchemeMaker::isWorkDone(CSession::const_iterator iter,
                                 CSession::const_iterator sentinel) const {
  return (iter == sentinel) && KeysBuilt_.empty();
}

bool CKeySchemeMaker::isPressingNext(CSession::const_iterator iter,
                                     CSession::const_iterator sentinel) const {
  if (iter == sentinel)
    return false;
  if (KeysBuilt_.empty())
    return true;
  return iter->getPressingTime() < KeysBuilt_.getFirstReleaseTime();
}

void CKeySchemeMaker::handlePressing(CSession::const_iterator* piter) {
  KeysBuilt_.insertKey(*piter);
  ++(*piter);
}

void CKeySchemeMaker::handleReleasing(const CFingerLayout& Layout,
                                      CKeyScheme* pKeyScheme) {
  CFinger KeyFinger = Layout.find(KeysBuilt_.getTopPosition());
  pKeyScheme->add(KeyFinger, KeysBuilt_.getAndRelease().Segment);
}

} // namespace NSKernel
} // namespace NSApplication
