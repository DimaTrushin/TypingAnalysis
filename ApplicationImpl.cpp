#include "ApplicationImpl.h"

#include "AppStatusAccess.h"
#include "Kernel/SeanceManagerImpl.h"
#include "KeyboardHandlerAccess.h"

namespace NSApplication {

CApplicationImpl::CApplicationImpl()
    : KeyboardShutter_(CKeyboardHandlerAccess().operator->()),
      SessionFlusher_(SeanceManager_.operator->()) {
  CAppStatusAccess AppStatus;
  AppStatus->subscribeToAppState(KeyboardShutter_.input());
  AppStatus->subscribeToAppState(SessionFlusher_.input());

#ifdef KEYBOARD_HANDLER_DEBUG
  {
    CKeyboardHandlerAccess KeyboardHandler;
    KeyboardHandler->subscribeToKeyPressing(
        KeyboardHandlerOut_->keyPressingInput());
    KeyboardHandler->subscribeToKeyReleasing(
        KeyboardHandlerOut_->keyReleasingInput());
  }
#endif

#ifdef SEANCE_MANAGER_DEBUG
  SeanceManager_->subscribeToCurrentSeance(
      SeanceManagerOut_->currentSeanceInput());
  SeanceManager_->subscribeToCurrentSeance(
      SeanceManagerOut_->currentSeanceTreeInput());
#endif

  SeanceManager_->subscribeToCurrentSeance(
      SessionSelectorOut_->currentSeanceInput());
  SeanceManager_->subscribeToCurrentSeance(
      SessionSelector_->currentSeanceInput());
  SessionSelectorOut_->subscribeToSessionIndex(
      SessionSelector_->sessionIndexInput());
  SessionSelector_->subscribeToSelectedSession(TextModule_->sessionInput());
  TextModuleOut_->subscribeToTextMode(TextModule_->textModeInput());
  TextModule_->subscribeToText(TextModuleOut_->textInput());
}

} // namespace NSApplication
