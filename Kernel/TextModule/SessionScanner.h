#ifndef NSAPPLICATION_NSKERNEL_NSSESSIONSCANNER_CSESSIONSCANNER_H
#define NSAPPLICATION_NSKERNEL_NSSESSIONSCANNER_CSESSIONSCANNER_H

#include "Kernel/KeyEvent.h"
#include "Kernel/Session.h"

namespace NSApplication {
namespace NSKernel {

namespace NSSessionScanner {
class CSessionScanner {
  using CKeyTextData = NSApplication::NSKeyboard::CKeyTextData;

public:
  QString* run(const CSession&, QString*);

private:
  void processSession(const CSession&);
  void processKeyEvent(const CKeyEvent&);
  QChar getSymbol(const CKeyEvent&, int);

  void setInternalResourses(QString*);
  void preallocateText(const CSession&);

  size_t getSessionTextSize(const CSession&);
  size_t getKeyEventSize(const CKeyEvent&);

  QString* Text_;
};
} // namespace NSSessionScanner

} // namespace NSKernel
} // namespace NSApplication

#endif
