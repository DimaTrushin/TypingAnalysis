#ifndef NSAPPLICATION_CTIMERACCESS_H
#define NSAPPLICATION_CTIMERACCESS_H

#include "Library/Singleton/AnyGlobalAccess.h"
#include "Timer.h"

namespace NSApplication {
namespace NSTimerDetail {

namespace nl = NSLibrary;

class CMainTimer;

class CMainTimerInitializer : ::NSLibrary::CAnyGlobalInitializer<CTimer, CMainTimer> {
  using CBase = ::NSLibrary::CAnyGlobalInitializer<CTimer, CMainTimer>;

public:
  using CBase::CBase;
};

class CMainTimerAccess : public ::NSLibrary::CAnyGlobalAccess<CTimer, CMainTimer> {};
} // namespace NSTimerDetail

using CTimerInit = NSTimerDetail::CMainTimerInitializer;
using CTimerAccess = NSTimerDetail::CMainTimerAccess;

} // namespace NSApplication

#endif // NSAPPLICATION_CTIMERACCESS_H
