#ifndef NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H

#include "Kernel/TextModule.h"
#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

#include <memory>

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeControllerDetail {
class CTextModeControllerImpl {
  using CTextModuleImpl = NSKernel::CTextModule::CImplementation;
  using ETextMode = NSKernel::ETextMode;

  using CTextModeObserver = NSLibrary::CObserver<ETextMode>;
  using CTextModeInput = NSLibrary::CColdInput<ETextMode>;

public:
  CTextModeControllerImpl(CTextModuleImpl*);

  CTextModeObserver* textModeInput();

private:
  void handleTextMode(const ETextMode& Mode);

  CTextModuleImpl* TextModule_;
  CTextModeInput TextModeInput_;
};

} // namespace NSTextModeControllerDetail

using CTextModeController = NSLibrary::CControllerWrapper<
    NSTextModeControllerDetail::CTextModeControllerImpl>;
} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H
