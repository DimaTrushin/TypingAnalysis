#include "SeanceViewController.h"

namespace NSApplication {
namespace NSInterface {
namespace NSSeanceViewControllerDetail {

CSeanceViewControllerImpl::CSeanceViewControllerImpl(
    CSessionSelectorImpl* Model)
    : Model_(Model),
      IndexInput_([this](Index index) { Model_->setCurrentSession(index); }) {
  assert(Model_);
}

CSeanceViewControllerImpl::CIndexObserver*
CSeanceViewControllerImpl::indexInput() {
  return &IndexInput_;
}

} // namespace NSSeanceViewControllerDetail

// namespace NSSeanceViewControllerDetail
} // namespace NSInterface
} // namespace NSApplication
