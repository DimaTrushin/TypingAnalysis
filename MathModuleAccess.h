#ifndef NSAPPLICATION_CMATHMODULEACCESS_H
#define NSAPPLICATION_CMATHMODULEACCESS_H

#include "Compute/Math.h"
#include "Library/Singleton/AnyGlobalAccess.h"

namespace NSApplication {
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

} // namespace NSApplication

#endif // NSAPPLICATION_CMATHMODULEACCESS_H
