#include "ParallelPpl.h"

namespace NSApplication {
namespace NSCompute {

CParallelPpl::CParallelPpl() {
  scheduler = concurrency::Scheduler::Create(concurrency::SchedulerPolicy{});
  // TO DO
  // Need to set minimal amount of threads
  scheduler->Attach();
}

CParallelPpl::~CParallelPpl() {
  concurrency::CurrentScheduler::Detach();
  // Do I need to wait until all the tasks are completed?
}

} // namespace NSCompute
} // namespace NSApplication
