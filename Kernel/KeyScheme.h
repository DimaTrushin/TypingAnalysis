#ifndef NSAPPLICATION_NSKERNEL_CKEYSCHEME_H
#define NSAPPLICATION_NSKERNEL_CKEYSCHEME_H

#include <vector>

#include "Kernel/FingerLayout.h"
#include "Keyboard/KeyTextData.h"
#include "TimeApp.h"

namespace NSApplication {
namespace NSKernel {

namespace NSKeySchemeDetail {

struct CSegment {
  CTime EndTime;
  unsigned char Multiplicity;
};

class CKeySegment {
  using CSegmentContainer = std::vector<CSegment>;
  using CIndex = int64_t;
  using CKeyTextData = NSKeyboard::CKeyTextData;

public:
  CKeySegment(CKeyTextData Symbol, CTime PressingTime);
  void AddSegment(unsigned char Multiplicity, CTime EndTime);

  CIndex getNumberOfSegments() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;

private:
  CKeyTextData Symbol_;
  CTime PressingTime_;
  CSegmentContainer Segments_;
};

} // namespace NSKeySchemeDetail

class CKeyScheme {
  using CKeySegment = NSKeySchemeDetail::CKeySegment;
  using CKeySegmentContainer = std::vector<CKeySegment>;
  using CSchemeContainer =
      std::map<CFinger, CKeySegmentContainer, CFinger::CStandardOrder>;

public:
private:
  CSchemeContainer Data_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYSCHEME_H
