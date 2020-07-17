#ifndef NSAPPLICATION_NSKEYBOARD_CANYKEYBOARDKILLER_H
#define NSAPPLICATION_NSKEYBOARD_CANYKEYBOARDKILLER_H

#include "Library/AnyObject/AnyMovable.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSKeyboardKillerDetail {

namespace nl = NSLibrary;

template<class TBase>
class IAnyKeyboardKiller : public TBase {
public:
  virtual void stopListener() const = 0;
protected:
  virtual ~IAnyKeyboardKiller() = default;
};

template<class TBase, class TObject>
class CAnyKeyboardKillerImpl : public TBase {
  using CBase = TBase;
public:
  using CBase::CBase;
  void stopListener() const {
    CBase::Object().stopListener();
  }
};

using CAnyKeyboardKiller = nl::CAnyMovable<IAnyKeyboardKiller, CAnyKeyboardKillerImpl>;
} // NSKeyboardKillerDetail

class CAnyKeyboardKiller : public NSKeyboardKillerDetail::CAnyKeyboardKiller {
  using CBase = NSKeyboardKillerDetail::CAnyKeyboardKiller;
public:
  using CBase::CBase;
};

} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CANYKEYBOARDKILLER_H
