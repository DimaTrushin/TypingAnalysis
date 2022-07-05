#ifndef NSAPPLICATION_NSLOCAL_CLANGUAGES_H
#define NSAPPLICATION_NSLOCAL_CLANGUAGES_H

#include "LocaleID.h"
#include <array>

namespace NSApplication {
namespace NSLocal {

struct CLanguages {
  static constexpr std::array<const char*, ELocale::End> Lang{"English",
                                                              "Русский"};
};

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CLANGUAGES_H
