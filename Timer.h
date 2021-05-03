#ifndef NSAPPLICATION_CTIMER_H
#define NSAPPLICATION_CTIMER_H

#include "TimeApp.h"

#include <chrono>

namespace NSApplication {

class CTimer {
public:
  CTimer();
  CTime get() const;

private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CTIMER_H
