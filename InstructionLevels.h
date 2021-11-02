#ifndef INSTRUCTIONLEVELS_H
#define INSTRUCTIONLEVELS_H

namespace NSApplication {

struct CInstrLevel {
  using type = int;
  enum : type {
    IL80386 = 0,
    Default = IL80386,
    SSE = 1,
    SSE2 = 2,
    SSE3 = 3,
    SSSE3 = 4,
    SSE4_1 = 5,
    SSE4_2 = 6,
    AVX = 7,
    AVX2 = 8,
    AVX512F = 9,
    AVX512VL = 10,
    AVX512BW = 11,
    AVX512DQ = AVX512BW
  };
};

} // namespace NSApplication

#endif // INSTRUCTIONLEVELS_H
