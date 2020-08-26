#ifndef NSAPPLICATION_NSQT_CAPPSTATUS_H
#define NSAPPLICATION_NSQT_CAPPSTATUS_H

#include "Library/Observer/Observer.h"
#include "AppState.h"

#include <QObject>

namespace NSApplication {
namespace NSQt {

class CAppStatus : public QObject {
  Q_OBJECT

  using CObservalbeState = NSLibrary::CObservableData<EAppState>;
  using CStateObserver = NSLibrary::CObserver<EAppState>;
public:
  CAppStatus();

  void subscribeToAppState(CStateObserver* Observer);

public slots:
  void applicationStateChanged(Qt::ApplicationState);

private:
  void connectToAppState();

  CObservalbeState AppState_;
};

} // NSQt
} // NSApplication

#endif // NSAPPLICATION_NSQT_CAPPSTATUS_H
