#ifndef NSAPPLICATION_NSKERNEL_NSSESSIONSELECTOR_CSESSIONSELECTOR_H
#define NSAPPLICATION_NSKERNEL_NSSESSIONSELECTOR_CSESSIONSELECTOR_H

#include "Kernel/Seance.h"
#include "Library/Observer/Observer.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {

namespace NSSessionSelectorDetail {

class CSessionSelectorImpl : public QObject {

public:
  using CSessionGetType = typename NSLibrary::CSource<CSession>::CGetType;
  using CSessionObservable = NSLibrary::CObservable<CSession>;
  using CSessionObserver = NSLibrary::CObserver<CSession>;

  using CSeanceGetType = typename NSLibrary::CSource<CSeance>::CGetType;
  using CSeanceInput = NSLibrary::CHotActiveInput<CSeance>;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;

  using CSessionIndexObserver = NSLibrary::CObserver<int>;
  using CSessionIndexInput = NSLibrary::CColdInput<int>;

  CSessionSelectorImpl();
  void subscribeToSelectedSession(CSessionObserver*);

  CSeanceObserver* currentSeanceInput();
  CSessionIndexObserver* sessionIndexInput();

private:
  void storeCurrentSeance(const CSeance&);

  void sendUndefinedIndex();
  void processSessionIndex(int);
  void pickSession(int);
  void resetSession();

  bool seanceIsUploaded();
  bool indexIsDefined(int);

  CSeanceInput CurrentSeanceInput_;
  CSessionIndexInput SessionIndexInput_;
  CSessionObservable SelectedSessionOutput_;

  CSeanceGetType CurrentSeance_;
  CSessionGetType SelectedSession_;
};
} // namespace NSSessionSelectorDetail

namespace NSSessionSelector {
class CSessionSelector {
  using CSessionSelectorImpl = NSSessionSelectorDetail::CSessionSelectorImpl;

public:
  CSessionSelector();
  CSessionSelectorImpl* operator->();

private:
  std::unique_ptr<CSessionSelectorImpl> Impl_;
};
} // namespace NSSessionSelector

} // namespace NSKernel
} // namespace NSApplication

#endif
