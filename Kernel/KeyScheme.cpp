#include "KeyScheme.h"

namespace NSApplication {
namespace NSKernel {

NSKeySchemeDetail::CKeySegment::CKeySegment(QString Text, CTime PressingTime)
    : Text_(Text), PressingTime_(PressingTime) {
}

NSKeySchemeDetail::CKeySegment::CKeySegment(QChar Symbol, CTime PressingTime)
    : Text_(Symbol), PressingTime_(PressingTime) {
}

void NSKeySchemeDetail::CKeySegment::AddSegment(unsigned char Multiplicity,
                                                CTime EndTime) {
  Segments_.emplace_back<CSegment>({EndTime, Multiplicity});
}

void NSKeySchemeDetail::CKeySegment::addText(QString Text) {
  Text_.append(Text);
}

NSKeySchemeDetail::CKeySegment::CIndex
NSKeySchemeDetail::CKeySegment::getNumberOfSegments() const {
  return Segments_.size();
}

CTime NSKeySchemeDetail::CKeySegment::getPressingTime() const {
  return PressingTime_;
}

CTime NSKeySchemeDetail::CKeySegment::getReleasingTime() const {
  if (Segments_.empty())
    return PressingTime_;
  return Segments_.back().EndTime;
}

const QString& NSKeySchemeDetail::CKeySegment::getText() const {
  return Text_;
}

CKeyScheme::CKeyScheme(CSchemeContainer&& Data) : Data_(std::move(Data)) {
}

void CKeyScheme::add(CFinger Finger, CKeySegment&& Segment) {
  Data_[Finger].push_back(Segment);
}

CKeyScheme CKeyScheme::getDefaultEmpty() {
  return CSchemeContainer{
      {CFinger::LeftIndex(), {}},   {CFinger::LeftMiddle(), {}},
      {CFinger::LeftRing(), {}},    {CFinger::LeftPinky(), {}},
      {CFinger::RightThumb(), {}},  {CFinger::RightIndex(), {}},
      {CFinger::RightMiddle(), {}}, {CFinger::RightRing(), {}},
      {CFinger::RightPinky(), {}},  {{}, {}}};
} // namespace NSKernel

} // namespace NSKernel
} // namespace NSApplication
