#ifndef NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATAFILLER_H
#define NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATAFILLER_H

#include "KeyFlags.h"
#include "ModifiersTextData.h"
#include "Session.h"
#include "TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

class CModifiersTextDataFiller {
public:
  void fill(const CSession& Session, const CTextDataTree& TextTree,
            CModifiersTextData* pData);

private:
  void fill(const CSession& Session, const CTextDataTree& TextTree,
            CKeyFlags Modifier, CModifierData* pData);
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATAFILLER_H
