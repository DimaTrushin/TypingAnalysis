#include "ApplicationImpl.h"

#include "AppStatusAccess.h"
#include "KeyboardHandlerAccess.h"

namespace NSApplication {

CApplicationImpl::CApplicationImpl()
    : KeyboardShutter_(CKeyboardHandlerAccess().operator->()),
      SessionFlusher_(SeanceManager_.model()),
      SeanceViewController_(SessionSelector_.model()),
      TextModeController_(TextModule_.model()) {
  CAppStatusAccess AppStatus;
  AppStatus->subscribeToAppState(KeyboardShutter_->input());
  AppStatus->subscribeToAppState(SessionFlusher_->input());

  SessionSelector_->subscribeToSeanceViewData(
      MainSeanceView_->currentSeanceViewDataInput());
  MainSeanceView_->subscribeToSessionIndex(SeanceViewController_->indexInput());
  SessionSelector_->subscribeToCurrentSession(
      TextModule_->currentSessionInput());

  TextModule_->subscribeToCurrentTextMode(TextModeView_->textModeInput());
  TextModeView_->subscribeToTextMode(TextModeController_->textModeInput());

  TextModule_->subscribeToTextData(MainTextPrinter_->textDataInput());

  AnalyticalModule_->subscribeToSpeedData(SpeedPlotter_->speedDataInput());
  TextModule_->subscribeToTextData(StatisticsView_->textDataInput());

#ifdef KEYBOARD_HANDLER_DEBUG
  {
    CKeyboardHandlerAccess KeyboardHandler;
    KeyboardHandler->subscribeToKeyPressing(
        KeyboardHandlerOut_->keyPressingInput());
    KeyboardHandler->subscribeToKeyReleasing(
        KeyboardHandlerOut_->keyReleasingInput());
  }
#endif
}

} // namespace NSApplication
