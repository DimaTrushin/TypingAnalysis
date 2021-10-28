#include "SessionSelector.h"

#include <QDebug>

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
  assert(SessionIndex < 0 ||
         size_t(SessionIndex) < Seance_.data()->get().size());
  if (SessionIndex_ == SessionIndex)
    return;
  SessionIndex_ = SessionIndex;
  Session_.notify();
}

void CSessionSelectorImpl::handleSeance(const CSeance& Seance) {
  qDebug() << "handleSeance";
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
  return !(SessionIndex_ < 0 || !Seance_.hasValue());
}

CSessionSelectorImpl::CSessionGetType
CSessionSelectorImpl::getCurrentSession() const {
  if (!hasCurrentSession())
    return CSessionGetType();
  return getCurrentSessionFromSeance(*Seance_.data());
}

CSessionSelectorImpl::CSessionGetType
CSessionSelectorImpl::getCurrentSessionFromSeance(const CSeance& Seance) const {
  return Seance[SessionIndex_];
}
} // namespace NSSessionSelectorDetail

CSessionSelector::CSessionSelector()
    : Impl_(std::make_unique<CSessionSelectorImpl>()) {
}

CSessionSelector::CSessionSelectorImpl* CSessionSelector::operator->() const {
  return Impl_.get();
}

CSessionSelector::CSessionSelectorImpl* CSessionSelector::model() const {
  return Impl_.get();
}

} // namespace NSKernel
} // namespace NSApplication
