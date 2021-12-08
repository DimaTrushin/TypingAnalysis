#include "PerformanceLogger.h"

#include "TimerAccess.h"
#include <QDebug>

namespace NSAppDebug {

CTimeAnchor::CTimeAnchor(const char* msg)
    : Begin_(NSApplication::CTimerAccess()->get()), Message_(msg) {
}

CTimeAnchor::~CTimeAnchor() {
  if (isActive_) {
    CTime Ellapsed = NSApplication::CTimerAccess()->get() - Begin_;
    qDebug() << Message_ << Ellapsed.toMicroSecondsI() << "mc";
  }
}

void CTimeAnchor::stop() {
  isActive_ = false;
  CTime Ellapsed = NSApplication::CTimerAccess()->get() - Begin_;
  qDebug() << Message_ << Ellapsed.toMicroSecondsI() << "mc";
}

} // namespace NSAppDebug
