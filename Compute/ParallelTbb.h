#ifndef NSAPPLICATION_NSCOMPUTE_CPARALLELTBB_H
#define NSAPPLICATION_NSCOMPUTE_CPARALLELTBB_H

#include <tbb/blocked_range.h>
#include <tbb/tbb.h>

namespace NSApplication {
namespace NSCompute {

class CParallelTbb {
public:
  CParallelTbb(size_t InitIter = kDefaultAmountOfIterations);

  template<class TIndex, class TFunction>
  void for_(TIndex begin, TIndex end, const TFunction& func) {
    tbb::parallel_for(tbb::blocked_range<TIndex>(begin, end),
                      [&func](tbb::blocked_range<TIndex>& r) {
                        for (TIndex it = r.begin(); it != r.end(); ++it) {
                          func(it);
                        }
                      });
  }

private:
  static constexpr size_t kDefaultAmountOfIterations = 1000;
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CPARALLELTBB_H
