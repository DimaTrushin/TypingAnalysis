#ifndef NSAPPLICATION_CPARALLELMODULEACCESS_H
#define NSAPPLICATION_CPARALLELMODULEACCESS_H

#include "Compute/ParallelModule.h"
#include "Library/Singleton/AnyGlobalAccess.h"

namespace NSApplication {

namespace NSParallelModuleDetail {
namespace nl = NSLibrary;

class CMainParallelModule;

using CParallelModule = NSCompute::CParallelModuleImpl;

class CMainParallelModuleInitializer
    : nl::CAnyGlobalInitializer<CParallelModule, CMainParallelModule> {
  using CBase = nl::CAnyGlobalInitializer<CParallelModule, CMainParallelModule>;

public:
  using CBase::CBase;
};

class CMainParallelModuleAccess
    : public nl::CAnyGlobalAccess<CParallelModule, CMainParallelModule> {
  using CBase = nl::CAnyGlobalAccess<CParallelModule, CMainParallelModule>;
};

} // namespace NSParallelModuleDetail

using CParallelInit = NSParallelModuleDetail::CMainParallelModuleInitializer;
using CParallelAccess = NSParallelModuleDetail::CMainParallelModuleAccess;

} // namespace NSApplication

#endif // NSAPPLICATION_CPARALLELMODULEACCESS_H
