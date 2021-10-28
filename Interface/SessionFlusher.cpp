#include "SessionFlusher.h"

namespace NSApplication {
namespace NSInterface {

namespace NSSessionFlusherDetailImpl {
CSessionFlusherImpl::CSessionFlusherImpl(CSeanceManagerImpl* SeanceManager)
    : SeanceManager_(SeanceManager),
      StateObserver_([this](EAppState State) { makeSessions(State); }) {
}

CSessionFlusherImpl::CStateObserver* CSessionFlusherImpl::input() {
  return &StateObserver_;
}

void CSessionFlusherImpl::makeSessions(EAppState State) {
  if (State == EAppState::Active)
    SeanceManager_->makeSessions();
}
} // namespace NSSessionFlusherDetailImpl

} // namespace NSInterface
} // namespace NSApplication
