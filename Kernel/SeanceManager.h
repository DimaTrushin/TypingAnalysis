#ifndef NSAPPLICATION_NSKERNEL_CSEANCEMANAGER_H
#define NSAPPLICATION_NSKERNEL_CSEANCEMANAGER_H

#include <memory>

namespace NSApplication {
namespace NSKernel {

class CSeanceManagerImpl;

class CSeanceManager {

public:
  CSeanceManager();
  ~CSeanceManager();

  CSeanceManagerImpl* operator->() const;

private:
  std::unique_ptr<CSeanceManagerImpl> Impl_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CSEANCEMANAGER_H
