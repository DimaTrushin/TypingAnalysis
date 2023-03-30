#ifndef NSAPPLICATION_NSKERNEL_CTEXTDATA_H
#define NSAPPLICATION_NSKERNEL_CTEXTDATA_H

#include "ModifiersTextData.h"
#include "Session.h"
#include "SessionTextSequencer.h"
#include "TextDataTree.h"
#include "TextSequencer.h"
#include "TextTreeSequencer.h"

#include <memory>

namespace NSApplication {
namespace NSKernel {

class CTextData {
public:
  CTextData(const CSession& Session, const CTextDataTree& TextTree,
            const CModifiersTextData& ModifiersData, CTextMode TextMode);

  const CSession& rawSession() const;
  const CTextDataTree& textTree() const;
  const CModifiersTextData& modifiersData() const;
  CTextMode textInfo() const;

  ETextMode textMode() const;
  EModifierMode shiftMode() const;
  EModifierMode ctrlMode() const;
  EModifierMode altMode() const;

  CSessionTextSequencer sessionSequencer() const;
  CFullTextSequencer fullTextSequencer() const;
  CPrintedTextSequencer printedTextSequencer() const;

private:
  std::reference_wrapper<const CSession> Session_;
  std::reference_wrapper<const CTextDataTree> TextTree_;
  std::reference_wrapper<const CModifiersTextData> ModifiersData_;
  CTextMode TextMode_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTDATA_H
