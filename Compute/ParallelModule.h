#ifndef NSAPPLICATION_NSCOMPUTE_CPARALLELMODULE_H
#define NSAPPLICATION_NSCOMPUTE_CPARALLELMODULE_H

#include <QtGlobal>

#include <memory>

#ifdef Q_OS_WIN
#include "ParallelWin.h"

namespace NSApplication {
namespace NSCompute {

class CParallelModule : public CParallelWin {
  using CBase = CParallelWin;
  using CBase::CBase;
};

} // namespace NSCompute
} // namespace NSApplication

#endif // Q_OS_WIN

#ifdef Q_OS_MACOS
#include "ParallelMac.h"

namespace NSApplication {
namespace NSCompute {

class CParallelModule : public CParallelMac {
  using CBase = CParallelMac;
  using CBase::CBase;
};

} // namespace NSCompute
} // namespace NSApplication
#endif // Q_OS_MACOS

#ifdef Q_OS_LINUX
#include "ParallelLin.h"

namespace NSApplication {
namespace NSCompute {

class CParallelModule : public CParallelLin {
  using CBase = CParallelLin;
  using CBase::CBase;
};

} // namespace NSCompute
} // namespace NSApplication
#endif // Q_OS_LINUX

#endif // NSAPPLICATION_NSCOMPUTE_CPARALLELMODULE_H
