#ifndef NSAPPLICATION_CQTLOOPEXCEPTION_H
#define NSAPPLICATION_CQTLOOPEXCEPTION_H

#include "Library/Singleton/AnyGlobalAccess.h"
#include "Qt/QtLoopExceptionHandler.h"

namespace NSApplication {

// class CLoggerCounterID;
// class CLoggerCounterInitializer :
//   CAnyGlobalInitializer<int, CLoggerCounterID> {
//   using CBase = CAnyGlobalInitializer<int, CLoggerCounterID>;
// public:
//   using CBase::CBase;
// };
// class CLoggerCounterAccess : public CAnyGlobalAccess<int, CLoggerCounterID> {};
//

namespace NSQtLoopExceptionHandlerDetail {
namespace nl = NSLibrary;
namespace nq = NSQt;

class CQtLoopExceptionMain;

class CQtLoopExceptionInit
  : nl::CAnyGlobalInitializer<nq::CQtLoopExceptionHandler, CQtLoopExceptionMain> {
  using CBase = nl::CAnyGlobalInitializer<nq::CQtLoopExceptionHandler, CQtLoopExceptionMain>;
public:
  using CBase::CBase;
};

class CQtLoopExceptionAccess
  : public nl::CAnyGlobalAccess<nq::CQtLoopExceptionHandler, CQtLoopExceptionMain> {};
}

using CQtLoopExceptionInit = NSQtLoopExceptionHandlerDetail::CQtLoopExceptionInit;
using CQtLoopException = NSQtLoopExceptionHandlerDetail::CQtLoopExceptionAccess;

} // NSApplication

#endif // NSAPPLICATION_CQTLOOPEXCEPTION_H
