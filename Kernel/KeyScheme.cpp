#include "KeyScheme.h"

namespace NSApplication {
namespace NSKernel {

NSKeySchemeDetail::CKeySegment::CKeySegment(QString Text, CTime PressingTime)
    : Text_(std::move(Text)), PressingTime_(PressingTime) {
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

NSKeySchemeDetail::CKeySegment::iterator
NSKeySchemeDetail::CKeySegment::begin() {
  return Segments_.begin();
}

NSKeySchemeDetail::CKeySegment::const_iterator
NSKeySchemeDetail::CKeySegment::begin() const {
  return Segments_.begin();
}

NSKeySchemeDetail::CKeySegment::const_iterator
NSKeySchemeDetail::CKeySegment::cbegin() const {
  return Segments_.cbegin();
}

NSKeySchemeDetail::CKeySegment::iterator NSKeySchemeDetail::CKeySegment::end() {
  return Segments_.end();
}

NSKeySchemeDetail::CKeySegment::const_iterator
NSKeySchemeDetail::CKeySegment::end() const {
  return Segments_.end();
}

NSKeySchemeDetail::CKeySegment::const_iterator
NSKeySchemeDetail::CKeySegment::cend() const {
  return Segments_.cend();
}

CKeyScheme::CKeyScheme(CSchemeContainer&& Data) : Data_(std::move(Data)) {
}

void CKeyScheme::add(CFinger Finger, CKeySegment&& Segment) {
  Data_[Finger].push_back(std::move(Segment));
}

CKeyScheme CKeyScheme::getDefaultEmpty() {
  return CSchemeContainer{
      {CFinger::LeftIndex(), {}},   {CFinger::LeftMiddle(), {}},
      {CFinger::LeftRing(), {}},    {CFinger::LeftPinky(), {}},
      {CFinger::RightThumb(), {}},  {CFinger::RightIndex(), {}},
      {CFinger::RightMiddle(), {}}, {CFinger::RightRing(), {}},
      {CFinger::RightPinky(), {}},  {{}, {}}};
}

CKeyScheme::iterator CKeyScheme::begin() {
  return Data_.begin();
}

CKeyScheme::const_iterator CKeyScheme::begin() const {
  return Data_.begin();
}

CKeyScheme::const_iterator CKeyScheme::cbegin() const {
  return Data_.cbegin();
}

CKeyScheme::iterator CKeyScheme::end() {
  return Data_.end();
}

CKeyScheme::const_iterator CKeyScheme::end() const {
  return Data_.end();
}

CKeyScheme::const_iterator CKeyScheme::cend() const {
  return Data_.cend();
}

size_t CKeyScheme::size() const {
  return Data_.size();
}

} // namespace NSKernel
} // namespace NSApplication
