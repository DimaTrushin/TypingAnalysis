#include "TextData.h"

namespace NSApplication {
namespace NSKernel {

CTextData::CConstFullTextProxy CTextData::textConstFullView() const {
  return TextTree.get()->textConstFullView();
}

CTextData::CConstPrintedTextProxy CTextData::textConstPrintedView() const {
  return TextTree.get()->textConstPrintedView();
}

} // namespace NSKernel
} // namespace NSApplication
