#include "SimdDetector.h"
#include "3dparty/vectorclass/instrset.h"

namespace NSApplication {

CSimdDetector::CSimdDetector() : InstructionLevel_(instrset_detect()) {
}

int CSimdDetector::level() const {
  return InstructionLevel_;
}
} // namespace NSApplication
