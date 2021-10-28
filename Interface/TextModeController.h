#ifndef NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H

#include <memory>

#include "Kernel/TextModule.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeControllerDetail {
class CTextModeControllerImpl {
  using CTextModuleImpl = NSKernel::CTextModule::CImplementation;
  using CTextMode = NSKernel::CTextMode;

  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeInput = NSLibrary::CColdInput<CTextMode>;

public:
  CTextModeControllerImpl(CTextModuleImpl*);

  CTextModeObserver* textModeInput();

private:
  void handleTextMode(const CTextMode& Mode);

  CTextModuleImpl* TextModule_;
  CTextModeInput TextModeInput_;
};

} // namespace NSTextModeControllerDetail

using CTextModeController = NSLibrary::CControllerWrapper<
    NSTextModeControllerDetail::CTextModeControllerImpl>;
} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H
