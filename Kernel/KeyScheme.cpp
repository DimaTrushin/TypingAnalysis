#include "KeyScheme.h"

namespace NSApplication {
namespace NSKernel {

NSKeySchemeDetail::CKeySegment::CKeySegment(CKeyTextData Symbol,
                                            CTime PressingTime)
    : Symbol_(Symbol), PressingTime_(PressingTime) {
}

void NSKeySchemeDetail::CKeySegment::AddSegment(unsigned char Multiplicity,
                                                CTime EndTime) {
  Segments_.emplace_back<CSegment>({EndTime, Multiplicity});
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

} // namespace NSKernel
} // namespace NSApplication
