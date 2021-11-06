#ifndef NSAPPLICATION_NSCOMPUTE_CPARALLELPPL_H
#define NSAPPLICATION_NSCOMPUTE_CPARALLELPPL_H

#include <ppl.h>

namespace NSApplication {
namespace NSCompute {

class CParallelPpl {
public:
  CParallelPpl();
  ~CParallelPpl();

  template<class TIndex, class TFunction>
  void for_(TIndex begin, TIndex end, const TFunction& func) {
    concurrency::parallel_for(begin, end, func);
  }

private:
  concurrency::Scheduler* scheduler;
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CPARALLELPPL_H
