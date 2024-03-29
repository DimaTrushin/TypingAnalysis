#ifndef NSAPPLICATION_NSKERNEL_CTEXTMODE_H
#define NSAPPLICATION_NSKERNEL_CTEXTMODE_H

namespace NSApplication {
namespace NSKernel {

enum class ETextMode : unsigned char { Raw, Full, Printed };

enum class EModifierMode : unsigned char { Non, All, Essential };

struct CModifiersMode {
  EModifierMode ShiftMode = EModifierMode::Non;
  EModifierMode CtrlMode = EModifierMode::Non;
  EModifierMode AltMode = EModifierMode::Non;

  friend bool operator==(const CModifiersMode& lhs, const CModifiersMode& rhs) {
    return lhs.ShiftMode == rhs.ShiftMode && lhs.CtrlMode == rhs.CtrlMode &&
           lhs.AltMode == rhs.AltMode;
  }
  friend bool operator!=(const CModifiersMode& lhs, const CModifiersMode& rhs) {
    return !(lhs == rhs);
  }
};

struct CTextMode {
  ETextMode TextMode = ETextMode::Printed;
  CModifiersMode Modifiers;

  friend bool operator==(const CTextMode& lhs, const CTextMode& rhs) {
    return lhs.TextMode == rhs.TextMode && lhs.Modifiers == rhs.Modifiers;
  }
  friend bool operator!=(const CTextMode& lhs, const CTextMode& rhs) {
    return !(lhs == rhs);
  }
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTMODE_H
