#ifndef NSAPPDEBUG_CSEANCEMANAGERDEBUGOUT_H
#define NSAPPDEBUG_CSEANCEMANAGERDEBUGOUT_H

#include "Interface/SeanceView.h"
#include "Kernel/Seance.h"
#include "Library/Observer/Observer.h"

#include <memory>

namespace NSApplication {
namespace NSQt {
class CMainWindow;
}
} // namespace NSApplication

namespace NSAppDebug {

class CSeanceManagerDebugGUI;

namespace NSSeanceManagerDebugOutDetail {

class CSeanceManagerDebugOutImpl {
  using CSession = NSApplication::NSKernel::CSession;

  using CSeance = NSApplication::NSKernel::CSeance;
  using CSeanceInput = NSLibrary::CHotInput<CSeance>;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;

  using CSeanceView = NSApplication::NSInterface::CSimpleSeanceView;

  using CMainWindow = NSApplication::NSQt::CMainWindow;

public:
  CSeanceManagerDebugOutImpl(CMainWindow* MainWindow);
  ~CSeanceManagerDebugOutImpl();

  CSeanceObserver* currentSeanceInput();
  CSeanceObserver* currentSeanceTreeInput();

private:
  void outputCurrentSeance(const CSeance& Seance);
  QString getSessionText(const CSession& Session);

  std::unique_ptr<CSeanceManagerDebugGUI> ui_;
  CSeanceView CurrentSeanceTreeView_;
  CSeanceInput CurrentSeanceInput_;
};

} // namespace NSSeanceManagerDebugOutDetail

class CSeanceManagerDebugOut {
  using CMainWindow = NSApplication::NSQt::CMainWindow;
  using CSeanceManagerDebugOutImpl =
      NSSeanceManagerDebugOutDetail::CSeanceManagerDebugOutImpl;

public:
  CSeanceManagerDebugOut(CMainWindow* MainWindow);

  CSeanceManagerDebugOutImpl* operator->();

private:
  std::unique_ptr<CSeanceManagerDebugOutImpl> Impl_;
};

} // namespace NSAppDebug

#endif // NSAPPDEBUG_CSEANCEMANAGERDEBUGOUT_H
