#ifndef NSAPPLICATION_NSKERNEL_CSESSION_H
#define NSAPPLICATION_NSKERNEL_CSESSION_H

#include "KeyEvent.h"

#include <vector>

namespace NSApplication {
namespace NSKernel {

class CSession : protected std::vector<CKeyEvent> {
  using CBase = std::vector<CKeyEvent>;

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
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSESSION_H
