#include "PplModule.h"

namespace NSApplication {

#ifdef _MSC_VER
CParallelModulePpl::CParallelModulePpl() {
  scheduler = concurrency::Scheduler::Create(concurrency::SchedulerPolicy{});
  scheduler->Attach();
}

CParallelModulePpl::~CParallelModulePpl() {
  concurrency::CurrentScheduler::Detach();
}
#endif

} // namespace NSApplication
