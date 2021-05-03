#include "AppStatus.h"

#include <QApplication>

#include <stdexcept>

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
    AppState_.set(EAppState::Active);
    return;
  }
  if (State == Qt::ApplicationInactive || State == Qt::ApplicationHidden) {
    AppState_.set(EAppState::Inactive);
    return;
  }
}

void CAppStatus::connectToAppState() {
  if (!QObject::connect(qApp, &QApplication::applicationStateChanged, this,
                        &CAppStatus::applicationStateChanged))
    throw std::runtime_error(
        "Cannot connect CAppStatus to Application Status!\n");
}

} // namespace NSQt
} // namespace NSApplication
