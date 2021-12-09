#include "PerformanceLogger.h"

#include <QDebug>

namespace NSAppDebug {

CTimeAnchor::CTimeAnchor(const char* msg) : Message_(msg) {
}

CTimeAnchor::~CTimeAnchor() {
  if (isActive_) {
    qDebug() << Message_ << Timer.get().toMicroSecondsI() << "mc";
  }
}

void CTimeAnchor::stop() {
  isActive_ = false;
  qDebug() << Message_ << Timer.get().toMicroSecondsI() << "mc";
}

} // namespace NSAppDebug
