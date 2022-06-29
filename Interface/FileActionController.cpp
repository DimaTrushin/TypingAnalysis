#include "FileActionController.h"

namespace NSApplication {
namespace NSInterface {

NSFileActionControllerDetail::CFileActionControllerImpl::
    CFileActionControllerImpl(CSeanceManagerImpl* SeanceManager)
    : SeanceManager_(SeanceManager),
      FileActionInput_(
          [this](const CFileCommand& Command) { handleFileAction(Command); }) {
}

NSFileActionControllerDetail::CFileActionControllerImpl::CFileActionObserver*
NSFileActionControllerDetail::CFileActionControllerImpl::fileActionInput() {
  return &FileActionInput_;
}

void NSFileActionControllerDetail::CFileActionControllerImpl::handleFileAction(
    const CFileCommand& Command) {
  switch (Command.Action) {
  case EFileAction::Save:
    SeanceManager_->saveFile(Command.Path);
    break;
  case EFileAction::Load:
    SeanceManager_->loadFile(Command.Path);
    break;
  default:
    break;
  }
}

} // namespace NSInterface
} // namespace NSApplication
