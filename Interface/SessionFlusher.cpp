#include "SessionFlusher.h"

#include "Kernel/SeanceManagerImpl.h"

namespace NSApplication {
namespace NSInterface {

CSessionFlusher::CSessionFlusher(CSeanceManagerImpl* SeanceManager)
    : SeanceManager_(SeanceManager),
      StateObserver_(std::make_unique<CStateObserverInput>(
          [this](EAppState State) { makeSessions(State); })) {
}

CSessionFlusher::CStateObserver* CSessionFlusher::input() {
  return StateObserver_.get();
}

void CSessionFlusher::makeSessions(EAppState State) {
  if (State == EAppState::Active)
    SeanceManager_->makeSessions();
}

} // namespace NSInterface
} // namespace NSApplication
