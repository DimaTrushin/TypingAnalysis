#ifndef NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H
#define NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H

#include "KeyEvent.h"

#include <list>
#include <optional>

namespace NSApplication {
namespace NSKernel {

class CSeance;

namespace NSSeanceMakerDetail {

class CPressedKeys : protected std::list<CKeyEvent*> {
  using CBase = std::list<CKeyEvent*>;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  using CBase::CBase;

  using CBase::begin;
  using CBase::clear;
  using CBase::empty;
  using CBase::end;
  using CBase::erase;
  using CBase::iterator;
  using CBase::push_back;
  using CBase::size;

  CBase::iterator findKey(CKeyPosition KeyPosition);
};

} // namespace NSSeanceMakerDetail

class CSeanceMaker {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyID = NSKeyboard::CKeyID;

  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CKeyReleasing = NSKeyboard::CKeyReleasing;

  using CRawSession = std::list<CKeyEvent>;
  using CRawSeance = std::list<CRawSession>;

  using CPressedKeys = NSSeanceMakerDetail::CPressedKeys;

  using CTimeOptional = std::optional<CTime>;

public:
  void add(const CKeyPressing& KeyPressing);
  void add(const CKeyReleasing& KeyReleasing);

  void resetTimeLimit();
  void setTimeLimit(CTime TimeLimit);
  CTimeOptional getTimeLimit() const;

  bool transferTo(CSeance* Seance);

private:
  void releaseAllKeysNow();
  bool needNewSession(const CKeyPressing& KeyPressing) const;
  void openNewSession();
  bool isAutoRepeatAllowed(CKeyID KeyID) const;

  CRawSession& CurrentSession();
  const CRawSession& CurrentSession() const;

  CRawSeance RawSeance_{1};
  CPressedKeys PressedKeys_;
  CTimeOptional TimeLimit_{Seconds(10)};
  CTime LastEvent_{};
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H
