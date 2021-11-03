#ifndef NSAPPLICATION_CSIMDDETECTORACCESS_H
#define NSAPPLICATION_CSIMDDETECTORACCESS_H

#include "Library/Singleton/AnyGlobalAccess.h"
#include "SimdDetector.h"

namespace NSApplication {
namespace NSSimdDetectorDetail {

namespace nl = NSLibrary;

class CMainSimdDetector;

class CMainSimdDetectorInitializer
    : nl::CAnyGlobalInitializer<CSimdDetector, CMainSimdDetector> {
  using CBase = nl::CAnyGlobalInitializer<CSimdDetector, CMainSimdDetector>;

public:
  using CBase::CBase;
};

class CMainSimdDetectorAccess
    : public nl::CAnyGlobalAccess<CSimdDetector, CMainSimdDetector> {};

} // namespace NSSimdDetectorDetail

using CSimdDetectorInit = NSSimdDetectorDetail::CMainSimdDetectorInitializer;
using CSimdDetectorAccess = NSSimdDetectorDetail::CMainSimdDetectorAccess;

} // namespace NSApplication

#endif // NSAPPLICATION_CSIMDDETECTORACCESS_H
