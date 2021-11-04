#include "ParallelPpl.h"

namespace NSApplication {
namespace NSCompute {

CParallelPpl::CParallelPpl() {
  scheduler = concurrency::Scheduler::Create(concurrency::SchedulerPolicy{});
  scheduler->Attach();
}

CParallelPpl::~CParallelPpl() {
  concurrency::CurrentScheduler::Detach();
}

} // namespace NSCompute
} // namespace NSApplication
