#ifndef NSAPPLICATION_NSKERNEL_CSESSION_H
#define NSAPPLICATION_NSKERNEL_CSESSION_H

#include "KeyEvent.h"

#include <boost/serialization/base_object.hpp>
#include <vector>

namespace NSApplication {
namespace NSKernel {

class CSession : protected std::vector<CKeyEvent> {
  using CBase = std::vector<CKeyEvent>;
  using CIndex = int64_t;

public:
  using CBase::CBase;

  using iterator = CBase::iterator;
  using const_iterator = CBase::const_iterator;

  using CBase::empty;
  using CBase::size;
  using CBase::operator[];

  using CBase::begin;
  using CBase::cbegin;
  using CBase::cend;
  using CBase::end;

private:
  friend boost::serialization::access;
  template<class TArchive>
  void serialize(TArchive& arch, const unsigned int) {
    arch& boost::serialization::base_object<CBase>(*this);
  }
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSESSION_H
