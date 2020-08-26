#include "SeanceManager.h"

#include "SeanceManagerImpl.h"


namespace NSApplication {
namespace NSKernel {

CSeanceManager::CSeanceManager()
  : Impl_(std::make_unique<CSeanceManagerImpl>()) {
}

CSeanceManagerImpl* CSeanceManager::operator->() const {
  return Impl_.get();
}

CSeanceManager::~CSeanceManager() = default;

} // NSKernel
} // NSApplication
