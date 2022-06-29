#ifndef NSAPPLICATION_NSKERNEL_CKEYEVENT_H
#define NSAPPLICATION_NSKERNEL_CKEYEVENT_H

#include "KeyFlags.h"
#include "Keyboard/RawKeyEvent.h"

#include <boost/serialization/access.hpp>

namespace NSApplication {
namespace NSKernel {

class CKeyEvent {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyID = NSKeyboard::CKeyID;
  using CKeyIDEnum = NSKeyboard::CKeyIDEnum;
  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CLabelData = NSKeyboard::CLabelData;
  using CKeyTextData = NSKeyboard::CKeyTextData;

public:
  CKeyEvent() = default;
  CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID, CLabelData KeyLabel,
            CKeyTextData KeyText, CTime PressingTime,
            CKeyFlags Flags = CKeyFlagsEnum::BasicKey);
  CKeyEvent(const CKeyPressing& PressingEvent,
            CKeyFlags Flags = CKeyFlagsEnum::BasicKey);

  void setReleasingTime(CTime ReleasingTime);

  bool isSameKey(const CKeyEvent& KeyEvent) const;
  bool isAutoRepeat() const;
  CKeyFlags getFlags() const;

  CKeyPosition getPosition() const;
  CKeyID getID() const;
  CLabelData getLabel() const;
  CKeyTextData getTextData() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  CTime getDuration() const;
  unsigned char getTextSize() const;
  bool hasText() const;
  QChar getSymbol(unsigned char index) const;
  QChar getLastSymbol() const;
  QString getText() const;

  bool isBackspace() const;
  bool isEnter() const;
  bool isSpace() const;
  bool isTab() const;
  bool isEscape() const;
  bool isControl() const;
  bool isShift() const;
  bool isCtrl() const;
  bool isAlt() const;
  bool isCapslock() const;

  // This is a key satisfying one of the condition above
  bool isTrackableSpecial() const;

  bool isShiftActive() const;
  bool isCtrlActive() const;
  bool isAltActive() const;
  bool isCapslockToggled() const;

  bool isDeadKey() const;
  bool isSilentDeadKey() const;

private:
  friend boost::serialization::access;
  template<class TArchive>
  void serialize(TArchive& arch, const unsigned int) {
    arch& KeyPosition_;
    arch& KeyID_;
    arch& KeyLabel_;
    arch& KeyText_;
    arch& Flags_;
    arch& PressingTime_;
    arch& ReleasingTime_;
  }

  CKeyPosition KeyPosition_;
  CKeyID KeyID_;
  CLabelData KeyLabel_;
  CKeyTextData KeyText_;
  CKeyFlags Flags_ = 0;
  CTime PressingTime_;
  CTime ReleasingTime_;
}; // namespace NSKernel

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYEVENT_H
