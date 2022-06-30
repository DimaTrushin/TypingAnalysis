#ifndef NSAPPLICATION_NSKERNEL_CSEANCE_H
#define NSAPPLICATION_NSKERNEL_CSEANCE_H

#include "Session.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/deque.hpp>
#include <deque>

namespace NSApplication {
namespace NSKernel {

class CSeance : protected std::deque<CSession> {
  using CBase = std::deque<CSession>;

public:
  using CBase::value_type;

  using CBase::CBase;
  using CBase::emplace_back;
  using CBase::push_back;
  using CBase::size;

  using CBase::begin;
  using CBase::cbegin;
  using CBase::cend;
  using CBase::end;

  using CBase::operator[];

private:
  friend boost::serialization::access;
  template<class TArchive>
  void serialize(TArchive& arch, const unsigned int) {
    arch& boost::serialization::base_object<CBase>(*this);
  }
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCE_H
