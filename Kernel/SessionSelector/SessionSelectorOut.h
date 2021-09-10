#include "Kernel/SessionSelector/SessionSelector.h"

#include "Interface/SeanceView.h"
#include "Kernel/Seance.h"
#include "Kernel/TextModule/SessionScanner.h"
#include "Library/Observer/Observer.h"

#include <memory>

namespace NSApplication {

namespace NSQt {
class CMainWindow;
}

namespace NSInterface {
class CSessionSelectorGUI;

namespace NSSessionSelectorOutDetail {
class CSessionSelectorOutImpl : public QObject {

  using CSessionSelectorImpl =
      NSApplication::NSKernel::NSSessionSelectorDetail::CSessionSelectorImpl;

  using CSession = NSApplication::NSKernel::CSession;
  using CSeance = NSApplication::NSKernel::CSeance;

  using CSeanceGetType = CSessionSelectorImpl::CSeanceGetType;
  using CSeanceInput = CSessionSelectorImpl::CSeanceInput;
  using CSeanceObserver = CSessionSelectorImpl::CSeanceObserver;

  using CSessionIndexObserver = CSessionSelectorImpl::CSessionIndexObserver;
  using CSessionIndexObservable = NSLibrary::CObservable<int>;

  using CSeanceView = NSApplication::NSInterface::CSeanceView;
  using CMainWindow = NSApplication::NSQt::CMainWindow;
  using CSessionScanner = NSKernel::NSSessionScanner::CSessionScanner;

public:
  CSessionSelectorOutImpl(CMainWindow*);
  ~CSessionSelectorOutImpl();

  void subscribeToSessionIndex(CSessionIndexObserver*);

  CSeanceObserver* currentSeanceInput();

private:
  void setUpUI();
  void connectUI();

  void processCurrentSeance(const CSeance&);
  void outputCurrentSeance(const CSeance&);

  void setUpRegularCase(const CSeance&);
  void setUpEmptyCase();
  void setUpNoSeanceCase();

  void updateSessionIndex();
  void resetSessionIndex();

  QString getSeanceDescription(const CSeance&);
  QString getSeanceSizeDescription(const CSeance&);
  QString getSessionDescription(int, const CSeance&);
  QString getSessionText(const CSession&);

  std::unique_ptr<CSessionSelectorGUI> ui_;

  CSeanceInput CurrentSeanceInput_;
  CSessionIndexObservable SessionIndexOutput_;

  CSessionScanner SessionScanner_;

  CSeanceGetType CurrentSeance_;
  int SessionIndex_;
};
} // namespace NSSessionSelectorOutDetail

namespace NSSessionSelectorOut {
class CSessionSelectorOut {
  using CMainWindow = NSApplication::NSQt::CMainWindow;
  using CSessionSelectorOutImpl =
      NSSessionSelectorOutDetail::CSessionSelectorOutImpl;

public:
  CSessionSelectorOut(CMainWindow*);
  CSessionSelectorOutImpl* operator->();

private:
  std::unique_ptr<CSessionSelectorOutImpl> Impl_;
};
} // namespace NSSessionSelectorOut

} // namespace NSInterface
} // namespace NSApplication
