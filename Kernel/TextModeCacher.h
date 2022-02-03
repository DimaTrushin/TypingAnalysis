#ifndef NSAPPLICATION_NSKERNEL_CTEXTMODECACHER_H
#define NSAPPLICATION_NSKERNEL_CTEXTMODECACHER_H

#include "Library/StlExtension/Cacher.h"
#include "Session.h"
#include "TextMode.h"

namespace NSApplication {
namespace NSKernel {

struct CTextCacheKey {
  const CSession* pSession;
  CTextMode TextMode;

  friend bool operator==(const CTextCacheKey& lhs, const CTextCacheKey& rhs);
  friend bool operator!=(const CTextCacheKey& lhs, const CTextCacheKey& rhs);
};

struct CTextCaheKeyHash {
  size_t operator()(const CTextCacheKey& Data) const;
  ;
};

template<class TData>
class CTextModeCacher
    : public NSLibrary::CCacher<CTextCacheKey, TData, CTextCaheKeyHash> {
  using CBase = NSLibrary::CCacher<CTextCacheKey, TData, CTextCaheKeyHash>;

public:
  using CBase::CBase;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTMODECACHER_H
