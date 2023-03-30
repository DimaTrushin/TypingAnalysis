#ifndef NSAPPLICATION_NSINTERFACE_CSEANCEVIEWCONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CSEANCEVIEWCONTROLLER_H

#include "Kernel/SessionSelector.h"
#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSInterface {

namespace NSSeanceViewControllerDetail {
class CSeanceViewControllerImpl {
  using Index = NSKernel::CSeanceViewData::Index;

  using CIndexInput = NSLibrary::CColdInput<Index>;
  using CIndexObserver = NSLibrary::CObserver<Index>;

public:
  using CSessionSelectorImpl = NSKernel::CSessionSelector::CImplementation;

  CSeanceViewControllerImpl(CSessionSelectorImpl* Model);

  CIndexObserver* indexInput();

private:
  CSessionSelectorImpl* Model_;
  CIndexInput IndexInput_;
};
} // namespace NSSeanceViewControllerDetail

using CSeanceViewController = NSLibrary::CControllerWrapper<
    NSSeanceViewControllerDetail::CSeanceViewControllerImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSEANCEVIEWCONTROLLER_H
