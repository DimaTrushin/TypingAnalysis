#ifndef NSAPPLICATION_CPPLMODULE_H
#define NSAPPLICATION_CPPLMODULE_H

#ifdef _MSC_VER
#include <ppl.h>
#else
#include <cstdint>
#endif

namespace NSApplication {

#ifdef _MSC_VER
class CParallelModulePpl {
public:
  CParallelModulePpl();
  ~CParallelModulePpl();

  template<typename TFunc>
  void parallel_for(size_t begin, size_t end, const TFunc& func) {
    concurrency::parallel_for(begin, end, [&func](size_t ind) { func(ind); });
  }

private:
  concurrency::Scheduler* scheduler;
};
#else
class CParallelModulePpl {
public:
  template<typename TFunc>
  void parallel_for(size_t begin, size_t end, const TFunc& func) {
    for (size_t i = begin; i != end; ++i)
      func(i);
  }
};
#endif
} // namespace NSApplication

#endif // NSAPPLICATION_CPPLMODULE_H
