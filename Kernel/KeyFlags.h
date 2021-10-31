#ifndef NSAPPLICATION_NSKERNEL_CKEYFLAGS_H
#define NSAPPLICATION_NSKERNEL_CKEYFLAGS_H

namespace NSApplication {
namespace NSKernel {

struct CKeyFlagsEnum {
  using CType = unsigned short;
  enum : CType {
    BasicKey = 0,
    Shift = 1,
    Ctrl = 2,
    Alt = 4,
    Capslock = 8,
    AutoRepeat = 256,
    DeadKey = 512
  };
};

using CKeyFlags = CKeyFlagsEnum::CType;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CKEYFLAGS_H
