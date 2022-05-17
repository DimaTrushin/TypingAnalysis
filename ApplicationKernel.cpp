#include "ApplicationKernel.h"

#include "KeyboardHandlerAccess.h"

namespace NSApplication {

CApplicationKernel::CApplicationKernel() {
  CKeyboardHandlerAccess KeyboardHandler;
  KeyboardHandler->subscribeToKeyPressing(SeanceManager_->pressingInput());
  KeyboardHandler->subscribeToKeyReleasing(SeanceManager_->releasingInput());

  SeanceManager_->subscribeToCurrentSeance(SessionSelector_->seanceInput());
  TextModule_->subscribeToTextData(AnalyticalModule_->textDataInput());

  TextModule_->subscribeToTextData(KeySchemeModule_->textDataInput());
  UserData_->subscribeToFingerLayout(KeySchemeModule_->fingerLayoutInput());

  TextModule_->subscribeToTextData(StatisticsModule_->textDataInput());
  LocalizationModule_->subscribeToStatisticsLocalizer(
      StatisticsModule_->localizerInput());
}

} // namespace NSApplication
