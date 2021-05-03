#include "ApplicationKernel.h"

#include "Kernel/SeanceManagerImpl.h"
#include "KeyboardHandlerAccess.h"

namespace NSApplication {

CApplicationKernel::CApplicationKernel() {
  CKeyboardHandlerAccess KeyboardHandler;
  KeyboardHandler->subscribeToKeyPressing(SeanceManager_->pressingInput());
  KeyboardHandler->subscribeToKeyReleasing(SeanceManager_->releasingInput());
}

} // namespace NSApplication
