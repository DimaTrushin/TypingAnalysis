#ifndef NSAPPLICATION_NSKERNEL_CSEANCE_H
#define NSAPPLICATION_NSKERNEL_CSEANCE_H

#include "Session.h"

namespace NSApplication {
namespace NSKernel {

class CSeance : protected std::list<CSession> {
  using CBase = std::list<CSession>;

public:
  using CBase::CBase;
  using CBase::emplace_back;
  using CBase::size;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCE_H
