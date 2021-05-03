#ifndef NSAPPLICATION_NSQT_CAPPSTATUS_H
#define NSAPPLICATION_NSQT_CAPPSTATUS_H

#include "AppState.h"
#include "Library/Observer/Observer.h"

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

} // namespace NSQt
} // namespace NSApplication

#endif // NSAPPLICATION_NSQT_CAPPSTATUS_H
