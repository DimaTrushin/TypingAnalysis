#ifndef NSAPPLICATION_NSKERNEL_CUNIVERSALTEXTSEQUENCER_H
#define NSAPPLICATION_NSKERNEL_CUNIVERSALTEXTSEQUENCER_H

#include "KeyStatus.h"
#include "Keyboard/KeyPosition.h"
#include "Library/AnyObject/AnyMovable.h"
#include "TimeApp.h"
#include <QChar>

namespace NSApplication {
namespace NSKernel {

namespace NSUniversalTextSequencerDetail {

template<class TBase>
class IUniversalTextSequencer : public TBase {
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  virtual bool isValid() const = 0;
  virtual void next() = 0;
  virtual EKeyStatus getStatus() const = 0;
  virtual unsigned char getDepth() const = 0;
  virtual CStatusData getStatusData() const = 0;
  virtual CKeyPosition getPosition() const = 0;
  virtual QChar getSymbol() const = 0;
  virtual CTime getPressingTime() const = 0;
  virtual CTime getReleasingTime() const = 0;
  virtual bool isAutoRepeat() const = 0;
};

template<class TBase, class TObject>
class CUniversalTextSequencerImpl : public TBase {
  using CBase = TBase;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  using CBase::CBase;
  bool isValid() const {
    return CBase::Object().isValid();
  }
  void next() {
    CBase::Object().next();
  }
  EKeyStatus getStatus() const {
    return CBase::Object().getStatus();
  }
  unsigned char getDepth() const {
    return CBase::Object().getDepth();
  }
  CStatusData getStatusData() const {
    return CBase::Object().getStatusData();
  }
  CKeyPosition getPosition() const {
    return CBase::Object().getPosition();
  }
  QChar getSymbol() const {
    return CBase::Object().getSymbol();
  }
  CTime getPressingTime() const {
    return CBase::Object().getPressingTime();
  }
  CTime getReleasingTime() const {
    return CBase::Object().getReleasingTime();
  }
  bool isAutoRepeat() const {
    return CBase::Object().isAutoRepeat();
  }
};

} // namespace NSUniversalTextSequencerDetail

class CUniversalTextSequencer
    : public NSLibrary::CAnyMovable<
          NSUniversalTextSequencerDetail::IUniversalTextSequencer,
          NSUniversalTextSequencerDetail::CUniversalTextSequencerImpl> {
  using CBase =
      CAnyMovable<NSUniversalTextSequencerDetail::IUniversalTextSequencer,
                  NSUniversalTextSequencerDetail::CUniversalTextSequencerImpl>;

public:
  using CBase::CBase;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CUNIVERSALTEXTSEQUENCER_H
