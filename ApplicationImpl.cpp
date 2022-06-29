#include "ApplicationImpl.h"

#include "AppStatusAccess.h"
#include "KeyboardHandlerAccess.h"

namespace NSApplication {

CApplicationImpl::CApplicationImpl()
    : KeyboardShutter_(CKeyboardHandlerAccess().operator->()),
      SessionFlusher_(SeanceManager_.model()),
      SeanceViewController_(SessionSelector_.model()),
      TextModeController_(TextModule_.model()),
      FileActionController_(SeanceManager_.model()),
      FileActionKeyboardBlocker_(CKeyboardHandlerAccess().operator->()) {
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

  KeySchemeModule_->subscribeToKeyScheme(KeySchemePlotter_->keySchemeInput());

  AppActions_.subscribeToFileAction(FileActionController_->fileActionInput());
  AppActions_.subscribeToFileActionBlocker(
      FileActionKeyboardBlocker_->fileActoinBlockInput());

  LocalizationModule_->subscribeToSeanceViewLocalizer(
      MainSeanceView_->localizerInput());
  LocalizationModule_->subscribeToTextModeViewLocalizer(
      TextModeView_->localizerInput());
  LocalizationModule_->subscribeToSpeedPlotterLocalizer(
      SpeedPlotter_->localizerInput());
  LocalizationModule_->subscribeToKeySchemePlotterLocalizer(
      KeySchemePlotter_->localizerInput());
  LocalizationModule_->subscribeToStatisticsViewLocalizer(
      StatisticsView_->localizerInput());

  StatisticsModule_->subscribeToStatisticsDescription(
      StatisticsView_->statisticsDescriptionInput());

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
