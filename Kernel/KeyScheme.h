#ifndef NSAPPLICATION_NSKERNEL_CKEYSCHEME_H
#define NSAPPLICATION_NSKERNEL_CKEYSCHEME_H

#include <vector>

#include <QString>

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

  using iterator = CSegmentContainer::iterator;
  using const_iterator = CSegmentContainer::const_iterator;

public:
  CKeySegment(QString Text, CTime PressingTime);
  CKeySegment(QChar Symbol, CTime PressingTime);
  void AddSegment(unsigned char Multiplicity, CTime EndTime);
  void addText(QString Text);

  CIndex getNumberOfSegments() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  const QString& getText() const;

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

private:
  QString Text_;
  CTime PressingTime_;
  CSegmentContainer Segments_;
};

} // namespace NSKeySchemeDetail

class CKeyScheme {
public:
  using CKeySegment = NSKeySchemeDetail::CKeySegment;
  using CKeySegmentContainer = std::vector<CKeySegment>;
  using CSchemeContainer =
      std::map<CFinger, CKeySegmentContainer, CFinger::CStandardOrder>;
  using iterator = CSchemeContainer::iterator;
  using const_iterator = CSchemeContainer::const_iterator;

  CKeyScheme() = default;

  void add(CFinger Finger, CKeySegment&& Segment);

  static CKeyScheme getDefaultEmpty();

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

  size_t size() const;

private:
  CKeyScheme(CSchemeContainer&& Data);
  CSchemeContainer Data_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYSCHEME_H
