#ifndef NSAPPLICATION_NSKERNEL_CTEXTDATA_H
#define NSAPPLICATION_NSKERNEL_CTEXTDATA_H

#include <memory>

#include "Kernel/Session.h"
#include "Kernel/TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

struct CTextData {
  using CFullTextProxy =
      NSTextDataTreeDetail::CTextDataTreeImpl::CFullTextProxy;
  using CConstFullTextProxy =
      NSTextDataTreeDetail::CTextDataTreeImpl::CConstFullTextProxy;
  using CPrintedTextProxy =
      NSTextDataTreeDetail::CTextDataTreeImpl::CPrintedTextProxy;
  using CConstPrintedTextProxy =
      NSTextDataTreeDetail::CTextDataTreeImpl::CConstPrintedTextProxy;

  CConstFullTextProxy textConstFullView() const;

  CConstPrintedTextProxy textConstPrintedView() const;

  const CSession& rawSession() const;

  std::reference_wrapper<const CSession> Session;
  std::reference_wrapper<const CTextDataTree> TextTree;
  CTextMode TextMode;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTDATA_H
