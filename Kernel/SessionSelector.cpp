#include "SessionSelector.h"

#include "AppDebug/PerformanceLogger.h"

namespace NSApplication {
namespace NSKernel {

namespace NSSessionSelectorDetail {
CSessionSelectorImpl::CSessionSelectorImpl()
    : Seance_([this](const CSeance& Seance) { handleSeance(Seance); }),
      Session_([this]() -> CSessionGetType { return getCurrentSession(); }) {
}

CSessionSelectorImpl::CSeanceObserver* CSessionSelectorImpl::seanceInput() {
  return &Seance_;
}

void CSessionSelectorImpl::subscribeToCurrentSession(CSessionObserver* obs) {
  assert(obs);
  Session_.subscribe(obs);
}

void CSessionSelectorImpl::subscribeToSeanceViewData(
    CSeanceViewDataObserver* obs) {
  assert(obs);
  SeanceViewData_.subscribe(obs);
}

void CSessionSelectorImpl::setCurrentSession(Index SessionIndex) {
  NSAppDebug::CTimeAnchor Anchor("set session & notify time = ");
  assert(SessionIndex < 0 || size_t(SessionIndex) < Seance_.data_().size());
  if (SessionIndex_ == SessionIndex)
    return;
  SessionIndex_ = SessionIndex;
  Session_.notify();
}

void CSessionSelectorImpl::handleSeance(const CSeance& Seance) {
  notifySeanceViewData(Seance);
  // TO DO
  // Do I need this in the future?
  //  if (hasCurrentSession())
  //    handleCurrentSession();
}

void CSessionSelectorImpl::notifySeanceViewData(const CSeance& Seance) {
  SeanceViewData_.set(CSeanceViewData{std::cref(Seance), SessionIndex_});
}

bool CSessionSelectorImpl::hasCurrentSession() const {
  return !(SessionIndex_ < 0 || !Seance_.hasData());
}

CSessionSelectorImpl::CSessionGetType
CSessionSelectorImpl::getCurrentSession() const {
  if (!hasCurrentSession())
    return CSessionGetType();
  return getCurrentSessionFromSeance(Seance_.data_());
}

CSessionSelectorImpl::CSessionGetType
CSessionSelectorImpl::getCurrentSessionFromSeance(const CSeance& Seance) const {
  return Seance[SessionIndex_];
}
} // namespace NSSessionSelectorDetail

} // namespace NSKernel
} // namespace NSApplication
