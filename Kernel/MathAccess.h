#ifndef NSAPPLICATION_NSKERNEL_CMATHACCESS_H
#define NSAPPLICATION_NSKERNEL_CMATHACCESS_H

#include "Compute/Math.h"
#include "Library/Singleton/AnyGlobalAccess.h"

namespace NSApplication {
namespace NSKernel {

namespace NSMathDetail {

using CMath = NSCompute::CMath;

class CMainMathModule;

namespace nl = NSLibrary;

class CMathInitializer : nl::CAnyGlobalInitializer<CMath, CMainMathModule> {
  using CBase = nl::CAnyGlobalInitializer<CMath, CMainMathModule>;

public:
  using CBase::CBase;
};

class CMathAccess : public nl::CAnyGlobalAccess<CMath, CMainMathModule> {};

} // namespace NSMathDetail

using CMathInit = NSMathDetail::CMathInitializer;
using CMathAccess = NSMathDetail::CMathAccess;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMATHACCESS_H
