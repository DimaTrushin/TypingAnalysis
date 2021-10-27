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

CSeanceViewController::CSeanceViewController(CSessionSelectorImpl* Model)
    : Impl_(std::make_unique<CSeanceViewControllerImpl>(Model)) {
}

CSeanceViewController::CSeanceViewControllerImpl*
CSeanceViewController::operator->() const {
  return Impl_.get();
}

// namespace NSSeanceViewControllerDetail
} // namespace NSInterface
} // namespace NSApplication
