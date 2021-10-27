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

void CSessionSelectorImpl::handleSeance(const CSeance& Seance) {
  // TO DO
  // This is just a preliminary version
  SeanceViewData_.set(CSeanceViewData{std::cref(Seance), CurrentSession_});
  qDebug() << "handleSeance";
}

CSessionSelectorImpl::CSessionGetType
CSessionSelectorImpl::getCurrentSession() const {
  if (CurrentSession_ < 0 || !Seance_.hasValue())
    return CSessionGetType();
  return getCurrentSessionFromSeance(*Seance_.data());
}

CSessionSelectorImpl::CSessionGetType
CSessionSelectorImpl::getCurrentSessionFromSeance(const CSeance& Seance) const {
  return Seance[CurrentSession_];
}
} // namespace NSSessionSelectorDetail

CSessionSelector::CSessionSelector()
    : Impl_(std::make_unique<CSessionSelectorImpl>()) {
}

CSessionSelector::CSessionSelectorImpl* CSessionSelector::operator->() const {
  return Impl_.get();
}

} // namespace NSKernel
} // namespace NSApplication
