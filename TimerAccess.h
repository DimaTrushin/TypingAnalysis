#ifndef NSAPPLICATION_CTIMERACCESS_H
#define NSAPPLICATION_CTIMERACCESS_H

#include "Library/Singleton/AnyGlobalAccess.h"
#include "Timer.h"

namespace NSApplication {
namespace NSTimerDetail {

namespace nl = NSLibrary;

class CMainTimer;

class CMainTimerInitializer : nl::CAnyGlobalInitializer<CTimer, CMainTimer> {
  using CBase = nl::CAnyGlobalInitializer<CTimer, CMainTimer>;

public:
  using CBase::CBase;
};

class CMainTimerAccess : public nl::CAnyGlobalAccess<CTimer, CMainTimer> {};
} // namespace NSTimerDetail

using CTimerInit = NSTimerDetail::CMainTimerInitializer;
using CTimerAccess = NSTimerDetail::CMainTimerAccess;

} // namespace NSApplication

#endif // NSAPPLICATION_CTIMERACCESS_H
