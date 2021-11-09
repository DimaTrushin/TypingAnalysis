#include "ParallelTbb.h"

namespace NSApplication {
namespace NSCompute {

CParallelTbb::CParallelTbb(size_t InitIter) {
  tbb::parallel_for(tbb::blocked_range<size_t>(0, InitIter),
                    [](tbb::blocked_range<size_t>& r) {
                      size_t p = 1;
                      for (size_t it = r.begin(); it != r.end(); ++it) {
                        for (size_t i = 0; i < 10000; ++i) {
                          for (size_t j = 0; j < 100; ++j) {
                            p += i * j;
                          }
                        }
                      }
                    });
}

} // namespace NSCompute
} // namespace NSApplication
