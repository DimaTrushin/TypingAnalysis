#include "KeyStatus.h"

namespace NSApplication {
namespace NSKernel {

bool operator==(CStatusData lhs, CStatusData rhs) {
  return lhs.Status == rhs.Status && lhs.Depth == rhs.Depth;
}

bool operator!=(CStatusData lhs, CStatusData rhs) {
  return !(lhs == rhs);
}

} // namespace NSKernel
} // namespace NSApplication
