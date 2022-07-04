#ifndef NSAPPLICATION_NSINTERFACE_CFILEACTIONCONTROLLER_H
#define NSAPPLICATION_NSINTERFACE_CFILEACTIONCONTROLLER_H

#include "FileMenu.h"
#include "Kernel/SeanceManager.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

namespace NSApplication {
namespace NSInterface {
namespace NSFileActionControllerDetail {

class CFileActionControllerImpl {
  using CFileActionObserver = NSLibrary::CObserver<CFileCommand>;
  using CFileActionInput = NSLibrary::CColdInput<CFileCommand>;

  using CSeanceManagerImpl = NSKernel::CSeanceManager::CImplementation;

public:
  CFileActionControllerImpl(CSeanceManagerImpl* SeanceManager);
  CFileActionObserver* fileActionInput();

private:
  void handleFileAction(const CFileCommand& Command);

  CSeanceManagerImpl* SeanceManager_;
  CFileActionInput FileActionInput_;
};

} // namespace NSFileActionControllerDetail

using CFileActionController = NSLibrary::CControllerWrapper<
    NSFileActionControllerDetail::CFileActionControllerImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CFILEACTIONCONTROLLER_H
