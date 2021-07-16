#include "ApplicationImpl.h"

#include "AppStatusAccess.h"
#include "Kernel/SeanceManagerImpl.h"
#include "KeyboardHandlerAccess.h"

namespace NSApplication {

CApplicationImpl::CApplicationImpl()
    : KeyboardShutter_(CKeyboardHandlerAccess().operator->()),
      SessionFlusher_(SeanceManager_.operator->())
#ifdef SEANCE_MANAGER_DEBUG
      ,
      SeanceManagerOut_(mainWindow())
#endif
{
  CAppStatusAccess AppStatus;
  AppStatus->subscribeToAppState(KeyboardShutter_.input());
  AppStatus->subscribeToAppState(SessionFlusher_.input());
#ifdef SEANCE_MANAGER_DEBUG
  SeanceManager_->subscribeToCurrentSeance(
      SeanceManagerOut_->currentSeanceInput());
#endif
} // namespace NSApplication

} // namespace NSApplication
