#ifndef NSAPPLICATION_NSKERNEL_NSTEXTMODULE_CTEXTMODULE_H
#define NSAPPLICATION_NSKERNEL_NSTEXTMODULE_CTEXTMODULE_H

#include "Kernel/Session.h"
#include "Library/Observer/Observer.h"
#include "SessionScanner.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {
namespace NSTextModuleDetail {

enum class CTextMode {
  Raw,
  Full,
  Printed,
};

class CTextModuleImpl : public QObject {

public:
  using CQStringGetType = typename NSLibrary::CSource<QString>::CGetType;
  using CQStringObservable = NSLibrary::CObservable<QString>;
  using CQStringObserver = NSLibrary::CObserver<QString>;

  using CSessionGetType = typename NSLibrary::CSource<CSession>::CGetType;
  using CSessionObserver = NSLibrary::CObserver<CSession>;
  using CSessionInput = NSLibrary::CObserverCold<CSession>;

  using CTextModeGetType = typename NSLibrary::CSource<CTextMode>::CGetType;
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeInput = NSLibrary::CHotActiveInput<CTextMode>;

  using CSessionScanner = NSSessionScanner::CSessionScanner;

  CTextModuleImpl();

  void subscribeToText(CQStringObserver*);

  CSessionObserver* sessionInput();
  CTextModeObserver* textModeInput();

private:
  void setSession(CSessionGetType);
  void setMode(CTextMode);

  void processSession();
  void makeText();

  void resetResources();
  void resetText();

  QString* scanSession();

  CSessionInput SessionInput_;
  CTextModeInput TextModeInput_;
  CQStringObservable TextOutput_;

  CSessionScanner SessionScanner_;

  CSessionGetType Session_;
  CTextMode Mode_;
  CQStringGetType Text_;
};

} // namespace NSTextModuleDetail

namespace NSTextModule {
class CTextModule {
  using CTextModuleImpl = NSTextModuleDetail::CTextModuleImpl;

public:
  CTextModule();
  CTextModuleImpl* operator->();

private:
  std::unique_ptr<CTextModuleImpl> Impl_;
};
} // namespace NSTextModule

} // namespace NSKernel
} // namespace NSApplication

#endif
