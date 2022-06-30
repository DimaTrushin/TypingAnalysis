#ifndef NSAPPLICATION_CAPPSTATUSACCESS_H
#define NSAPPLICATION_CAPPSTATUSACCESS_H

#include "Library/Singleton/AnyGlobalAccess.h"
#include "Qt/AppStatus.h"

namespace NSApplication {
namespace NSAppStatusAccessDetail {

namespace nl = NSLibrary;
namespace nq = NSQt;

class CAppStatusMain;

class CAppStatusInit
    : nl::CAnyGlobalInitializer<nq::CAppStatus, CAppStatusMain> {
  using CBase = nl::CAnyGlobalInitializer<nq::CAppStatus, CAppStatusMain>;

public:
  using CBase::CBase;
};

class CAppStatusAccess
    : public nl::CAnyGlobalAccess<nq::CAppStatus, CAppStatusMain> {};

} // namespace NSAppStatusAccessDetail

using CAppStatusInit = NSAppStatusAccessDetail::CAppStatusInit;
using CAppStatusAccess = NSAppStatusAccessDetail::CAppStatusAccess;

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPSTATUSACCESS_H
