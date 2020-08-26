#ifndef NSAPPLICATION_NSQT_CAPPSTATUS_H
#define NSAPPLICATION_NSQT_CAPPSTATUS_H

#include "Library/Observer/Observer.h"

#include <QObject>

namespace NSApplication {
namespace NSQt {

class CAppStatus : public QObject {
  Q_OBJECT
public:
  enum class EState : unsigned char {
    Active = 1,
    Inactive = 2,
  };

private:
  using CObservalbeState = NSLibrary::CObservableData<EState>;
  using CStateObserver = NSLibrary::CObserver<EState>;
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
