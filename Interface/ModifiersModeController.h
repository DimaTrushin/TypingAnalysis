#ifndef NSAPPLICATION_NSINTERFACE_CMODIFIERSMODECONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CMODIFIERSMODECONTROLLER_H

#include "Kernel/TextModule.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSInterface {

namespace NSModifiersModeControllerDetail {

class CModifiersModeControllerImpl {
  using CTextModuleImpl = NSKernel::CTextModule::CImplementation;
  using CModifiersMode = NSKernel::CModifiersMode;

  using CTextModeObserver = NSLibrary::CObserver<CModifiersMode>;
  using CTextModeInput = NSLibrary::CColdInput<CModifiersMode>;

public:
  CModifiersModeControllerImpl(CTextModuleImpl*);
  CTextModeObserver* textModeInput();

private:
  void handleTextMode(const CModifiersMode& Mode);

  CTextModuleImpl* TextModule_;
  CTextModeInput TextModeInput_;
};
} // namespace NSModifiersModeControllerDetail

using CModifiersModeController = NSLibrary::CControllerWrapper<
    NSModifiersModeControllerDetail::CModifiersModeControllerImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CMODIFIERSMODECONTROLLER_H
