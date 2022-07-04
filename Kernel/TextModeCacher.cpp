#include "TextModeCacher.h"

#include <boost/functional/hash.hpp>

namespace NSApplication {
namespace NSKernel {

bool operator==(const CTextCacheKey& lhs, const CTextCacheKey& rhs) {
  return lhs.pSession == rhs.pSession &&
         lhs.TextMode.TextMode == rhs.TextMode.TextMode &&
         (lhs.TextMode.TextMode == NSKernel::ETextMode::Raw ||
          lhs.TextMode == rhs.TextMode);
}

bool operator!=(const CTextCacheKey& lhs, const CTextCacheKey& rhs) {
  return !(lhs == rhs);
}

size_t CTextCaheKeyHash::operator()(const CTextCacheKey& Data) const {
  size_t seed = 0;
  boost::hash_combine(seed, Data.pSession);
  boost::hash_combine(seed, static_cast<unsigned char>(Data.TextMode.TextMode));
  if (Data.TextMode.TextMode != NSKernel::ETextMode::Raw) {
    boost::hash_combine(
        seed, static_cast<unsigned char>(Data.TextMode.Modifiers.ShiftMode));
    boost::hash_combine(
        seed, static_cast<unsigned char>(Data.TextMode.Modifiers.CtrlMode));
    boost::hash_combine(
        seed, static_cast<unsigned char>(Data.TextMode.Modifiers.AltMode));
  }
  return seed;
}

} // namespace NSKernel
} // namespace NSApplication
