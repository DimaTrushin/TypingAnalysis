#ifndef NSAPPDEBUG_CPERFORMANCELOGGER_H
#define NSAPPDEBUG_CPERFORMANCELOGGER_H

#include "Timer.h"

namespace NSAppDebug {

class CTimeAnchor {
  using CTimer = NSApplication::CTimer;
  using CTime = NSApplication::CTime;

public:
  CTimeAnchor(const char* msg);
  ~CTimeAnchor();

  void stop();

private:
  CTimer Timer;
  const char* Message_;
  bool isActive_ = true;
};

} // namespace NSAppDebug

#endif // NSAPPDEBUG_CPERFORMANCELOGGER_H
