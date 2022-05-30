#include "UniversalTextSequencer.h"

namespace NSApplication {
namespace NSKernel {

bool CUniversalTextSequencer::CFirstPressedOnTop::operator()(
    const CUniversalTextSequencer& lhs, const CUniversalTextSequencer& rhs) {
  if (!lhs->isValid())
    return false;
  if (!rhs->isValid())
    return true;
  return lhs->getPressingTime() > rhs->getPressingTime();
}

} // namespace NSKernel
} // namespace NSApplication
