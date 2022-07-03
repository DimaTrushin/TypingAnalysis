#include "FileActionKeyboardBlocker.h"
#include "Keyboard/KeyboardHandler.h"

namespace NSApplication {
namespace NSInterface {
namespace NSFileActionKeyboardBlockerDetail {

CFileActionKeyboardBlockerImpl::CFileActionKeyboardBlockerImpl(
    CKeyboardHandler* KeyboardHandler)
    : KeyboardHandler_(KeyboardHandler),
      FileActionBlockInput_(
          [this](EFileActionBlock Block) { handleBlock(Block); }) {
}

CFileActionKeyboardBlockerImpl::CFileActionBlockObserver*
NSFileActionKeyboardBlockerDetail::CFileActionKeyboardBlockerImpl::
    fileActoinBlockInput() {
  return &FileActionBlockInput_;
}

void CFileActionKeyboardBlockerImpl::handleBlock(EFileActionBlock Block) {
  switch (Block) {
  case EFileActionBlock::Activate:
    KeyboardHandler_->activate(NSKeyboard::CKeyboardBlock::Enum::FileAction);
    break;
  case EFileActionBlock::Deactivate:
    KeyboardHandler_->deactivate(NSKeyboard::CKeyboardBlock::Enum::FileAction);
    break;
  default:
    break;
  }
}
} // namespace NSFileActionKeyboardBlockerDetail
} // namespace NSInterface
} // namespace NSApplication
