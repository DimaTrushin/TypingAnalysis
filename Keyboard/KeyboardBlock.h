#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDBLOCK_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDBLOCK_H

#include "Library/StlExtension/Blocker.h"

namespace NSApplication {
namespace NSKeyboard {

namespace NSKeyboardBlockDetail {

struct CKeyboardBlockers {
  using CType = unsigned char;
  enum class Enum : CType {
    Active = 0,
    AppStatus = 1,
    FileAction = 2,
    UserBlock = 4
  };
};

} // namespace NSKeyboardBlockDetail

using CKeyboardBlock =
    NSLibrary::CBlock<NSKeyboardBlockDetail::CKeyboardBlockers>;

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDBLOCK_H
