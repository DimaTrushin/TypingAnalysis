#ifndef NSAPPLICATION_NSKERNEL_CFINGERLAYOUT_H
#define NSAPPLICATION_NSKERNEL_CFINGERLAYOUT_H

#include "Keyboard/KeyPosition.h"

#include <map>
#include <set>

namespace NSApplication {
namespace NSKernel {

class CFinger {
public:
  struct EFingerEnum {
    using CType = unsigned char;
    enum : CType {
      Left = 0,
      Right = 8,
      Thumb = 0,
      Index = 1,
      Middle = 2,
      Ring = 3,
      Pinky = 4,
      Undefined = 128,
      HandMask = 8,
      FingerMask = 7,
    };
  };
  using EFinger = EFingerEnum::CType;

  CFinger() = default;

  static CFinger LeftThumb();
  static CFinger LeftIndex();
  static CFinger LeftMiddle();
  static CFinger LeftRing();
  static CFinger LeftPinky();
  static CFinger RightThumb();
  static CFinger RightIndex();
  static CFinger RightMiddle();
  static CFinger RightRing();
  static CFinger RightPinky();

  bool isLeftHand() const;
  bool isRightHand() const;

  EFinger id() const;

  struct CLeftHandFirst {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CThumbFirst {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CDirectOrder {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CReverseOrder {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CUndefinedLast {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };

  struct CLeftReverseRightDirect {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };

  struct CStandardOrder {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };

private:
  CFinger(EFinger Finger);

  EFinger Finger_ = EFingerEnum::Undefined;
};

class CFingerLayout {
  using CKeyPosEnum = NSKeyboard::CKeyPosEnum;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyPositionContainer = std::set<CKeyPosition>;
  using CLayoutContainer =
      std::map<CFinger, CKeyPositionContainer, CFinger::CStandardOrder>;

public:
  CFingerLayout() = default;
  static CFingerLayout getDefault();
  CFinger find(CKeyPosition Position) const;

private:
  CFingerLayout(CLayoutContainer Layout);

  static CLayoutContainer getDefaultLayout();

  static CKeyPositionContainer getDefaultLeftThumb();
  static CKeyPositionContainer getDefaultLeftIndex();
  static CKeyPositionContainer getDefaultLeftMiddle();
  static CKeyPositionContainer getDefaultLeftRing();
  static CKeyPositionContainer getDefaultLeftPinky();
  static CKeyPositionContainer getDefaultRightThumb();
  static CKeyPositionContainer getDefaultRightIndex();
  static CKeyPositionContainer getDefaultRightMiddle();
  static CKeyPositionContainer getDefaultRightRing();
  static CKeyPositionContainer getDefaultRightPinky();

  CLayoutContainer Layout_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CFINGERLAYOUT_H
