#ifndef NSAPPDEBUG_CPERFORMANCELOGGER_H
#define NSAPPDEBUG_CPERFORMANCELOGGER_H

#include "TimeApp.h"

namespace NSAppDebug {

class CTimeAnchor {
  using CTime = NSApplication::CTime;

public:
  CTimeAnchor(const char* msg);
  ~CTimeAnchor();

  void stop();

private:
  CTime Begin_;
  const char* Message_;
  bool isActive_ = true;
};

} // namespace NSAppDebug

#endif // NSAPPDEBUG_CPERFORMANCELOGGER_H
