#ifndef NSAPPLICATION_NSKERNEL_CSTATISTICSDESCRIPTION_H
#define NSAPPLICATION_NSKERNEL_CSTATISTICSDESCRIPTION_H

#include <QString>
#include <deque>

namespace NSApplication {
namespace NSKernel {

struct CDescription {
  QString Data;
  QString Value;
  QString Hint;
};
using CStatisticsDescription = std::deque<CDescription>;

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSTATISTICSDESCRIPTION_H
