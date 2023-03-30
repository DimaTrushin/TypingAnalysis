#include "SimdDetector.h"

#include "3dparty/vectorclass/instrset.h"
#include "3dparty/vectorclass/vectorclass.h"

namespace NSApplication {

CSimdDetector::CSimdDetector() : InstructionLevel_(instrset_detect()) {
  no_subnormals();
}

int CSimdDetector::level() const {
  return InstructionLevel_;
}
} // namespace NSApplication
