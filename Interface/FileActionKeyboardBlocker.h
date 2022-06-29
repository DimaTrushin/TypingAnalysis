#ifndef NSAPPLICATION_NSINTERFACE_CFILEACTIONKEYBOARDBLOCKER_H
#define NSAPPLICATION_NSINTERFACE_CFILEACTIONKEYBOARDBLOCKER_H

#include "Actions.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSKeyboard {
class CKeyboardHandler;
} // namespace NSKeyboard

namespace NSInterface {
namespace NSFileActionKeyboardBlockerDetail {

class CFileActionKeyboardBlockerImpl {
  using CFileActionBlockObserver = NSLibrary::CObserver<EFileActionBlock>;
  using CFileActionBlockInput = NSLibrary::CColdInput<EFileActionBlock>;

  using CKeyboardHandler = NSKeyboard::CKeyboardHandler;

public:
  CFileActionKeyboardBlockerImpl(CKeyboardHandler* KeyboardHandler);

  CFileActionBlockObserver* fileActoinBlockInput();

private:
  void handleBlock(EFileActionBlock Block);

  CKeyboardHandler* KeyboardHandler_;
  CFileActionBlockInput FileActionBlockInput_;
};

} // namespace NSFileActionKeyboardBlockerDetail

using CFileActionKeyboardBlocker = NSLibrary::CControllerWrapper<
    NSFileActionKeyboardBlockerDetail::CFileActionKeyboardBlockerImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CFILEACTIONKEYBOARDBLOCKER_H
