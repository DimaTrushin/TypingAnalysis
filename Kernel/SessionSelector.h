#ifndef NSAPPLICATION_NSKERNEL_CSESSIONSELECTOR_H
#define NSAPPLICATION_NSKERNEL_CSESSIONSELECTOR_H

#include <memory>

#include "Kernel/Seance.h"
#include "Kernel/SeanceViewData.h"
#include "Library/Observer/Observer.h"

namespace NSApplication {
namespace NSKernel {

namespace NSSessionSelectorDetail {

class CSessionSelectorImpl {
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;
  using CSeanceInput = NSLibrary::CHotInput<CSeance>;

  using CSessionObservable = NSLibrary::CObservable<CSession>;
  using CSessionGetType = typename NSLibrary::CSource<CSession>::CGetType;
  using CSessionObserver = NSLibrary::CObserver<CSession>;

  using Index = CSeanceViewData::Index;

  using CSeanceViewDataObservable = NSLibrary::CObservableData<CSeanceViewData>;
  using CSeanceViewDataObserver = NSLibrary::CObserver<CSeanceViewData>;

public:
  CSessionSelectorImpl();

  CSeanceObserver* seanceInput();
  void subscribeToCurrentSession(CSessionObserver* obs);
  void subscribeToSeanceViewData(CSeanceViewDataObserver* obs);

  void setCurrentSession(Index);

private:
  void handleSeance(const CSeance& Seance);
  void notifySeanceViewData(const CSeance& Seance);

  bool hasCurrentSession() const;

  CSessionGetType getCurrentSession() const;
  CSessionGetType getCurrentSessionFromSeance(const CSeance&) const;

  CSeanceInput Seance_;
  CSessionObservable Session_;
  CSeanceViewDataObservable SeanceViewData_;
  Index SessionIndex_ = CSeanceViewData::kNotSelected;
};

} // namespace NSSessionSelectorDetail

class CSessionSelector {
public:
  using CSessionSelectorImpl = NSSessionSelectorDetail::CSessionSelectorImpl;
  CSessionSelector();

  CSessionSelectorImpl* operator->() const;
  CSessionSelectorImpl* model() const;

private:
  std::unique_ptr<CSessionSelectorImpl> Impl_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSESSIONSELECTOR_H
