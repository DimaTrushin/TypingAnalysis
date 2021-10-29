#include "SessionToTreeConverter.h"

#include "Session.h"
#include "TextDataTree.h"

#include <cassert>

namespace NSApplication {
namespace NSKernel {

void CSessionToTreeConverter::convert(const CSession& Source,
                                      CTextDataTree* pTarget) {
  assert(pTarget);
  CTextDataTree& Target = *pTarget;
  Target->clear();

  if (Source.empty())
    return;

  for (const auto& element : Source) {
    if (element.hasText())
      for (int i = 0; i < element.getTextSize(); ++i) {
        Target->add(element.getSymbol(i), ESymbolStatus::TextSymbol);
      }
    if (element.isBackspace())
      Target->deleteLastData();
  }
}

} // namespace NSKernel
} // namespace NSApplication
