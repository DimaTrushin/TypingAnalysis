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
};

} // NSKernel
} // NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSESSION_H
