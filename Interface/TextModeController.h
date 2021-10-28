#ifndef NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H

#include <memory>

#include "Kernel/TextModule.h"
#include "Library/Observer/Observer.h"

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeControllerDetail {
class CTextModeControllerImpl {
  using CTextModuleImpl = NSKernel::CTextModule::CTextModuleImpl;
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

class CTextModeController {
  using CTextModeControllerImpl =
      NSTextModeControllerDetail::CTextModeControllerImpl;
  using CTextModuleImpl = NSKernel::CTextModule::CTextModuleImpl;

public:
  CTextModeController(CTextModuleImpl*);

  CTextModeControllerImpl* operator->() const;

private:
  std::unique_ptr<CTextModeControllerImpl> Impl_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTMODECONTROLLER_H
