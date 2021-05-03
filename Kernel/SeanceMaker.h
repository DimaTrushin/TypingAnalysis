#ifndef NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H
#define NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H

#include "KeyEvent.h"

#include <list>
#include <optional>

namespace NSApplication {
namespace NSKernel {

class CSeance;

class CSeanceMaker {
  using CKeyPosition = NSKeyboard::CKeyPosition;

  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CKeyReleasing = NSKeyboard::CKeyReleasing;

  using CRawSession = std::list<CKeyEvent>;
  using CRawSeance = std::list<CRawSession>;

  using CPressedKeys = std::list<CKeyEvent*>;

  using CTimeOptional = std::optional<CTime>;

public:
  void add(const CKeyPressing& KeyPressing);
  void add(const CKeyReleasing& KeyReleasing);

  void setTimeLimit(CTime TimeLimit);
  CTimeOptional getTimeLimit() const;

  void transferTo(CSeance* Seance);

private:
  void releaseAllKeysNow();
  bool needNewSession(const CKeyPressing& KeyPressing) const;
  void openNewSession();

  CPressedKeys::iterator findKey(CKeyPosition KeyPosition);

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
