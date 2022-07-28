#ifndef NSAPPLICATION_NSINTERFACE_CSESSIONFLUSHER_H
#define NSAPPLICATION_NSINTERFACE_CSESSIONFLUSHER_H

#include "Kernel/SeanceManager.h"
#include "Library/Observer2/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Qt/AppState.h"

#include <memory>

namespace NSApplication {
namespace NSInterface {

namespace NSSessionFlusherDetailImpl {
class CSessionFlusherImpl {
  using CSeanceManager = NSKernel::CSeanceManager;
  using EAppState = NSQt::EAppState;
  using CStateObserverInput = NSLibrary::CHotInput<EAppState>;
  using CStateObserver = NSLibrary::CObserver<EAppState>;
  using CSeanceManagerImpl = CSeanceManager::CImplementation;

public:
  CSessionFlusherImpl(CSeanceManagerImpl*);

  CStateObserver* input();

private:
  void makeSessions(EAppState);

  CSeanceManagerImpl* SeanceManager_;
  CStateObserverInput StateObserver_;
};
} // namespace NSSessionFlusherDetailImpl

using CSessionFlusher = NSLibrary::CControllerWrapper<
    NSSessionFlusherDetailImpl::CSessionFlusherImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSESSIONFLUSHER_H
