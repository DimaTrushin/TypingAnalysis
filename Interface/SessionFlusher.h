#ifndef NSAPPLICATION_NSINTERFACE_CSESSIONFLUSHER_H
#define NSAPPLICATION_NSINTERFACE_CSESSIONFLUSHER_H

#include "Library/Observer/Observer.h"
#include "Qt/AppState.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {
class CSeanceManagerImpl;
} // namespace NSKernel

namespace NSInterface {

// TO DO
// I am not sure that this is an appropriate place to define the class
class CSessionFlusher {
  using EAppState = NSQt::EAppState;
  using CStateObserverInput = NSLibrary::CHotInput<EAppState>;
  using CStateObserver = NSLibrary::CObserver<EAppState>;
  using CSeanceManagerImpl = NSKernel::CSeanceManagerImpl;

public:
  CSessionFlusher(CSeanceManagerImpl*);

  CStateObserver* input();

private:
  void makeSessions(EAppState);

  CSeanceManagerImpl* SeanceManager_;
  std::unique_ptr<CStateObserverInput> StateObserver_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSESSIONFLUSHER_H
