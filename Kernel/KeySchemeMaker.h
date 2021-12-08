#ifndef NSAPPLICATION_NSKERNEL_CKEYSCHEMEMAKER_H
#define NSAPPLICATION_NSKERNEL_CKEYSCHEMEMAKER_H

#include "Kernel/FingerLayout.h"
#include "Kernel/KeyScheme.h"
#include "Kernel/Session.h"
#include "Kernel/TextData.h"
#include "Library/StlExtension/HeapWithAccess.h"

namespace NSApplication {
namespace NSKernel {

namespace NSKeySchemeMakerDetail {
struct CKeySegmentBuilt {
  using CKeySegment = NSKeySchemeDetail::CKeySegment;
  using CKeyPosition = NSKeyboard::CKeyPosition;

  CKeySegment Segment;
  CTime ReleasingTime;
  CKeyPosition KeyPosition;

  class CFirstReleasedOnTop {
  public:
    bool operator()(const CKeySegmentBuilt& first,
                    const CKeySegmentBuilt& second);
  };
};

class CKeySegmentsUnderConstruction {
  using CKeySegment = NSKeySchemeDetail::CKeySegment;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CContainer =
      NSLibrary::CHeapWithAccess<CKeySegmentBuilt,
                                 CKeySegmentBuilt::CFirstReleasedOnTop>;
  using CIndex = int64_t;

  template<class TIterator>
  QString getKeyText(TIterator iter);

public:
  CKeyPosition getTopPosition() const;
  CTime getFirstReleaseTime() const;
  bool empty() const;
  CIndex size() const;
  CKeySegmentBuilt getAndRelease();
  template<class TIterator>
  void insertKey(TIterator iter, CTime BeginTime);

private:
  void updateMultiplicities(CTime NewKeyTime);

  CContainer KeysBuilt_;
};

} // namespace NSKeySchemeMakerDetail

class CKeySchemeMaker {
  using CKeySegmentsUnderConstruction =
      NSKeySchemeMakerDetail::CKeySegmentsUnderConstruction;

public:
  CKeyScheme make(const CTextData& TextData, const CFingerLayout& Layout);

private:
  template<class TTextView>
  CKeyScheme makeScheme(const TTextView& TextView, const CFingerLayout& Layout);
  template<class TIterator>
  bool isWorkDone(TIterator iter, TIterator sentinel) const;
  template<class TIterator>
  bool isPressingNext(TIterator iter, TIterator sentinel) const;
  template<class TIterator>
  void handlePressing(TIterator*);
  void handleReleasing(const CFingerLayout&, CKeyScheme*);

  CKeySegmentsUnderConstruction KeysSegmentsBuilt_;
  CTime BeginTime_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYSCHEMEMAKER_H