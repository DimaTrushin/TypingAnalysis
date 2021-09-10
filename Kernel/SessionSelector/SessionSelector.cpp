#include "SessionSelector.h"

namespace NSApplication {
namespace NSKernel {

namespace NSSessionSelectorDetail {

CSessionSelectorImpl::CSessionSelectorImpl()
    : CurrentSeanceInput_(
          [this](const CSeance& Seance) { storeCurrentSeance(Seance); }),
      SessionIndexInput_(
          [this](int SessionIndex) { processSessionIndex(SessionIndex); }),
      SelectedSessionOutput_([this]() { return SelectedSession_; }) {
}

void CSessionSelectorImpl::subscribeToSelectedSession(
    CSessionObserver* observer) {
  SelectedSessionOutput_.subscribe(observer);
}

CSessionSelectorImpl::CSeanceObserver*
CSessionSelectorImpl::currentSeanceInput() {
  return &CurrentSeanceInput_;
}

CSessionSelectorImpl::CSessionIndexObserver*
CSessionSelectorImpl::sessionIndexInput() {
  return &SessionIndexInput_;
}

void CSessionSelectorImpl::storeCurrentSeance(const CSeance& Seance) {
  CurrentSeance_ = Seance;
  sendUndefinedIndex();
}

void CSessionSelectorImpl::sendUndefinedIndex() {
  processSessionIndex(-1);
}

void CSessionSelectorImpl::processSessionIndex(int SessionIndex) {
  if (seanceIsUploaded() && indexIsDefined(SessionIndex)) {
    pickSession(SessionIndex);
  } else {
    resetSession();
  }
  SelectedSessionOutput_.notify();
}

void CSessionSelectorImpl::pickSession(int SessionIndex) {
  assert(SessionIndex >= 0);
  assert(SessionIndex < CurrentSeance_->get().size());
  SelectedSession_ = CurrentSeance_->get()[SessionIndex];
}

void CSessionSelectorImpl::resetSession() {
  SelectedSession_.reset();
}

bool CSessionSelectorImpl::seanceIsUploaded() {
  return CurrentSeanceInput_.isActive();
}

bool CSessionSelectorImpl::indexIsDefined(int SessionIndex) {
  return (SessionIndex != -1);
}

} // namespace NSSessionSelectorDetail

namespace NSSessionSelector {

CSessionSelector::CSessionSelector()
    : Impl_(std::make_unique<CSessionSelectorImpl>()) {
}

CSessionSelector::CSessionSelectorImpl* CSessionSelector::operator->() {
  return Impl_.get();
}

} // namespace NSSessionSelector

} // namespace NSKernel
} // namespace NSApplication
