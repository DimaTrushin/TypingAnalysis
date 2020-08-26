#ifndef NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H
#define NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H

#include "KeyEvent.h"

#include <list>


namespace NSApplication {
namespace NSKernel {

class CSeanceMaker {
  using CKeyPosition = NSKeyboard::CKeyPosition;

  using CKeyPressing = NSKeyboard::CKeyPressing;
  using CKeyReleasing = NSKeyboard::CKeyReleasing;

  using CRawSession = std::list<CKeyEvent>;
  using CRawSeance = std::list<CRawSession>;

  using CPressedKeys = std::list<CKeyEvent*>;
public:
  void add(const CKeyPressing& KeyPressing);
  void add(const CKeyReleasing& KeyReleasing);

  // TO DO
  // add flushTo method or buffer access method
private:
  bool needNewSession(const CKeyPressing& KeyPressing) const;
  void openNewSession();

  CPressedKeys::iterator findKey(CKeyPosition KeyPosition);

  CRawSession& CurrentSession();

  CRawSeance RawSeance_{1};
  CPressedKeys PressedKeys_;
  CTime LastEvent_{};
};

} // NSKernel
} // NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEMAKER_H
