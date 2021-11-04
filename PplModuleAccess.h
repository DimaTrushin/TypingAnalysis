#ifndef NSAPPLICATION_CPPLMODULEACCESS_H
#define NSAPPLICATION_CPPLMODULEACCESS_H

#include "Library/Singleton/AnyGlobalAccess.h"
#include "PplModule.h"

namespace NSApplication {

namespace NSPplModuleDetail {
namespace nl = NSLibrary;

class CMainParallel;

class CMainParallelInitializer
    : nl::CAnyGlobalInitializer<CParallelModulePpl, CMainParallel> {
  using CBase = nl::CAnyGlobalInitializer<CParallelModulePpl, CMainParallel>;

public:
  using CBase::CBase;
};

class CMainParallelAccess
    : public nl::CAnyGlobalAccess<CParallelModulePpl, CMainParallel> {};

} // namespace NSPplModuleDetail

using CMainParallelInit = NSPplModuleDetail::CMainParallelInitializer;
using CMainParallelAccess = NSPplModuleDetail::CMainParallelAccess;

} // namespace NSApplication

#endif // NSAPPLICATION_CPPLMODULEACCESS_H
