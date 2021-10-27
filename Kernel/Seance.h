#ifndef NSAPPLICATION_NSKERNEL_CSEANCE_H
#define NSAPPLICATION_NSKERNEL_CSEANCE_H

#include "Session.h"

#include <deque>

namespace NSApplication {
namespace NSKernel {

class CSeance : protected std::deque<CSession> {
  using CBase = std::deque<CSession>;

public:
  using CBase::CBase;
  using CBase::emplace_back;
  using CBase::size;

  using CBase::begin;
  using CBase::cbegin;
  using CBase::cend;
  using CBase::end;

  using CBase::operator[];
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCE_H
