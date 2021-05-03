#include "Timer.h"

namespace NSApplication {

CTimer::CTimer() {
  start_ = std::chrono::steady_clock::now();
}

CTime CTimer::get() const {
  using namespace std::chrono;
  auto elapsed = duration_cast<microseconds>(steady_clock::now() - start_);
  return CTime(MicroSeconds(elapsed.count()));
}

} // namespace NSApplication
