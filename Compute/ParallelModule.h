#ifndef NSAPPLICATION_NSCOMPUTE_CPARALLELMODULE_H
#define NSAPPLICATION_NSCOMPUTE_CPARALLELMODULE_H

#include <QtGlobal>
#include <memory>

#ifdef Q_OS_WIN
#include "ParallelWin.h"

namespace NSApplication {
namespace NSCompute {
using CParallelModuleImpl = CParallelWin;

} // namespace NSCompute
} // namespace NSApplication

#endif // Q_OS_WIN

#ifdef Q_OS_MACOS
#include "ParallelMac.h"

namespace NSApplication {
namespace NSCompute {
using CParallelModuleImpl = CParallelMac;

} // namespace NSCompute
} // namespace NSApplication
#endif // Q_OS_MACOS

#ifdef Q_OS_LINUX
#include "ParallelLin.h"

namespace NSApplication {
namespace NSCompute {
using CParallelModuleImpl = CParallelLin;

} // namespace NSCompute
} // namespace NSApplication
#endif // Q_OS_LINUX

#endif // NSAPPLICATION_NSCOMPUTE_CPARALLELMODULE_H
