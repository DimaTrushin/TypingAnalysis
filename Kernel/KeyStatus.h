#ifndef NSAPPLICATION_NSKERNEL_CKEYSTATUS_H
#define NSAPPLICATION_NSKERNEL_CKEYSTATUS_H

namespace NSApplication {
namespace NSKernel {

enum EKeyStatus : unsigned char {
  MainText,
  AccidentallyDeleted,
  RequiredDeletion,
  Erroneous,
  Backspace,
  Control,
  EssentialControl,
  SilentDeadKey,
  Ignore,
  End,
};

struct CStatusData {
  EKeyStatus Status;
  unsigned char Depth;

  friend bool operator==(CStatusData lhs, CStatusData rhs);
  friend bool operator!=(CStatusData lhs, CStatusData rhs);
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYSTATUS_H
