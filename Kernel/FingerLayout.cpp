#include "FingerLayout.h"

#include <algorithm>
#include <cassert>

namespace NSApplication {
namespace NSKernel {

CFinger CFinger::LeftThumb() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Thumb);
}

CFinger CFinger::LeftIndex() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Index);
}

CFinger CFinger::LeftMiddle() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Middle);
}

CFinger CFinger::LeftRing() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Ring);
}

CFinger CFinger::LeftPinky() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Pinky);
}

CFinger CFinger::RightThumb() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Thumb);
}

CFinger CFinger::RightIndex() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Index);
}

CFinger CFinger::RightMiddle() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Middle);
}

CFinger CFinger::RightRing() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Ring);
}

CFinger CFinger::RightPinky() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Pinky);
}

bool CFinger::isLeftHand() const {
  return (Finger_ & EFingerEnum::HandMask) == EFingerEnum::Left;
}

bool CFinger::isRightHand() const {
  return (Finger_ & EFingerEnum::HandMask) == EFingerEnum::Right;
}

CFinger::CFinger(EFinger Finger) : Finger_(Finger) {
}

int CFinger::CLeftHandFirst::cmp(CFinger lhs, CFinger rhs) {
  return (rhs.Finger_ & EFingerEnum::HandMask) -
         (lhs.Finger_ & EFingerEnum::HandMask);
}

bool CFinger::CLeftHandFirst::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CThumbFirst::cmp(CFinger lhs, CFinger rhs) {
  return std::min((rhs.Finger_ & EFingerEnum::FingerMask), 1) -
         std::min((lhs.Finger_ & EFingerEnum::FingerMask), 1);
}

bool CFinger::CThumbFirst::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CDirectOrder::cmp(CFinger lhs, CFinger rhs) {
  return (rhs.Finger_ & EFingerEnum::FingerMask) -
         (lhs.Finger_ & EFingerEnum::FingerMask);
}

bool CFinger::CDirectOrder::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CReverseOrder::cmp(CFinger lhs, CFinger rhs) {
  return CDirectOrder::cmp(rhs, lhs);
}

bool CFinger::CReverseOrder::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CUndefinedLast::cmp(CFinger lhs, CFinger rhs) {
  return (rhs.Finger_ & EFingerEnum::Undefined) -
         (lhs.Finger_ & EFingerEnum::Undefined);
}

bool CFinger::CUndefinedLast::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CLeftReverseRightDirect::cmp(CFinger lhs, CFinger rhs) {
  if (CLeftHandFirst::cmp(lhs, rhs) != 0)
    return CLeftHandFirst::cmp(lhs, rhs);
  assert(lhs.isLeftHand() == rhs.isLeftHand());
  assert(lhs.isRightHand() == rhs.isRightHand());
  if (lhs.isLeftHand()) {
    return CReverseOrder::cmp(lhs, rhs);
  } else {
    return CDirectOrder::cmp(lhs, rhs);
  }
}

bool CFinger::CLeftReverseRightDirect::operator()(CFinger lhs,
                                                  CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CStandardOrder::cmp(CFinger lhs, CFinger rhs) {
  if (CUndefinedLast::cmp(lhs, rhs) != 0)
    return CUndefinedLast::cmp(lhs, rhs);
  if (CThumbFirst::cmp(lhs, rhs) != 0)
    return CThumbFirst::cmp(lhs, rhs);
  if (CLeftHandFirst::cmp(lhs, rhs) != 0)
    return CLeftHandFirst::cmp(lhs, rhs);
  return CLeftReverseRightDirect::cmp(lhs, rhs);
}

bool CFinger::CStandardOrder::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

CFingerLayout CFingerLayout::getDefault() {
  return CFingerLayout(getDefaultLayout());
}

CFinger CFingerLayout::find(CKeyPosition Position) const {
  for (const auto& FingerPair : Layout_) {
    if (FingerPair.second.count(Position) > 0)
      return FingerPair.first;
  }
  return CFinger();
}

CFingerLayout::CFingerLayout(CLayoutContainer Layout) : Layout_(Layout) {
}

CFingerLayout::CLayoutContainer CFingerLayout::getDefaultLayout() {
  CLayoutContainer Layout{{CFinger::LeftIndex(), getDefaultLeftIndex()},
                          {CFinger::LeftMiddle(), getDefaultLeftMiddle()},
                          {CFinger::LeftRing(), getDefaultLeftRing()},
                          {CFinger::LeftPinky(), getDefaultLeftPinky()},
                          {CFinger::RightThumb(), getDefaultRightThumb()},
                          {CFinger::RightIndex(), getDefaultRightIndex()},
                          {CFinger::RightMiddle(), getDefaultRightMiddle()},
                          {CFinger::RightRing(), getDefaultRightRing()},
                          {CFinger::RightPinky(), getDefaultRightPinky()},
                          {CFinger(), {}}};
  return Layout;
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftThumb() {
  return {};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftIndex() {
  return {CKeyPosEnum::AE05, CKeyPosEnum::AE06, CKeyPosEnum::AD04,
          CKeyPosEnum::AD05, CKeyPosEnum::AC04, CKeyPosEnum::AC05,
          CKeyPosEnum::AB04, CKeyPosEnum::AB05};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftMiddle() {
  return {CKeyPosEnum::AE04, CKeyPosEnum::AD03, CKeyPosEnum::AC03,
          CKeyPosEnum::AB03};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftRing() {
  return {CKeyPosEnum::AE03, CKeyPosEnum::AD02, CKeyPosEnum::AC02,
          CKeyPosEnum::AB02};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftPinky() {
  return {CKeyPosEnum::AE01, CKeyPosEnum::AE02, CKeyPosEnum::AD01,
          CKeyPosEnum::AC01, CKeyPosEnum::AB01, CKeyPosEnum::TLDE,
          CKeyPosEnum::TAB,  CKeyPosEnum::CAPS, CKeyPosEnum::LFSH,
          CKeyPosEnum::LCTL};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightThumb() {
  return {CKeyPosEnum::SPCE};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightIndex() {
  return {CKeyPosEnum::AE07, CKeyPosEnum::AE08, CKeyPosEnum::AD06,
          CKeyPosEnum::AD07, CKeyPosEnum::AC06, CKeyPosEnum::AC07,
          CKeyPosEnum::AB06, CKeyPosEnum::AB07};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightMiddle() {
  return {CKeyPosEnum::AE09, CKeyPosEnum::AD08, CKeyPosEnum::AC08,
          CKeyPosEnum::AB08};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightRing() {
  return {CKeyPosEnum::AE10, CKeyPosEnum::AD09, CKeyPosEnum::AC09,
          CKeyPosEnum::AB09};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightPinky() {
  return {CKeyPosEnum::AE11, CKeyPosEnum::AE12, CKeyPosEnum::AD10,
          CKeyPosEnum::AD11, CKeyPosEnum::AD12, CKeyPosEnum::AC10,
          CKeyPosEnum::AC11, CKeyPosEnum::AB10, CKeyPosEnum::BKSP,
          CKeyPosEnum::BKSL, CKeyPosEnum::RTRN, CKeyPosEnum::RTSH,
          CKeyPosEnum::RCTL};
}

} // namespace NSKernel
} // namespace NSApplication
