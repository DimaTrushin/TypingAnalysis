#include "AppStatus.h"

#include <QApplication>


namespace NSApplication {
namespace NSQt {

CAppStatus::CAppStatus() {
  connectToAppState();
}

void CAppStatus::subscribeToAppState(CAppStatus::CStateObserver* Observer) {
  assert(Observer);
  AppState_.subscribe(Observer);
}

void CAppStatus::applicationStateChanged(Qt::ApplicationState State) {
  if (State == Qt::ApplicationActive) {
    AppState_.set(EState::Active);
    return;
  }
  if (State == Qt::ApplicationInactive || State == Qt::ApplicationHidden) {
    AppState_.set(EState::Inactive);
    return;
  }
}

void CAppStatus::connectToAppState() {
  if (!QObject::connect(qApp,
                        &QApplication::applicationStateChanged,
                        this,
                        &CAppStatus::applicationStateChanged))
    throw std::exception("Cannot connect CAppStatus to Application Status!\n");

}

} // NSQt
} // NSApplication
