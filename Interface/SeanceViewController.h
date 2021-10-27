#ifndef NSAPPLICATION_NSINTERFACE_CSEANCEVIEWCONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CSEANCEVIEWCONTROLLER_H

#include "Kernel/SessionSelector.h"
#include "Library/Observer/Observer.h"

namespace NSApplication {
namespace NSInterface {

namespace NSSeanceViewControllerDetail {
class CSeanceViewControllerImpl {
  using Index = NSKernel::CSeanceViewData::Index;

  using CIndexInput = NSLibrary::CColdInput<Index>;
  using CIndexObserver = NSLibrary::CObserver<Index>;

public:
  using CSessionSelectorImpl = NSKernel::CSessionSelector::CSessionSelectorImpl;

  CSeanceViewControllerImpl(CSessionSelectorImpl* Model);

  CIndexObserver* indexInput();

private:
  CSessionSelectorImpl* Model_;
  CIndexInput IndexInput_;
};
} // namespace NSSeanceViewControllerDetail

class CSeanceViewController {
  using CSeanceViewControllerImpl =
      NSSeanceViewControllerDetail::CSeanceViewControllerImpl;
  using CSessionSelectorImpl = CSeanceViewControllerImpl::CSessionSelectorImpl;

public:
  CSeanceViewController(CSessionSelectorImpl*);

  CSeanceViewControllerImpl* operator->() const;

private:
  std::unique_ptr<CSeanceViewControllerImpl> Impl_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSEANCEVIEWCONTROLLER_H
