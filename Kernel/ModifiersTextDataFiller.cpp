#include "ModifiersTextDataFiller.h"

namespace NSApplication {
namespace NSKernel {

void CModifiersTextDataFiller::fill(const CSession& Session,
                                    const CTextDataTree& TextTree,
                                    CModifiersTextData* pData) {
  assert(pData);
  fill(Session, TextTree, CKeyFlagsEnum::Shift, &pData->Shifts);
  fill(Session, TextTree, CKeyFlagsEnum::Ctrl, &pData->Ctrls);
  fill(Session, TextTree, CKeyFlagsEnum::Alt, &pData->Alts);
}

void CModifiersTextDataFiller::fill(const CSession& Session,
                                    const CTextDataTree& TextTree,
                                    CKeyFlags Modifier, CModifierData* pData) {
  assert(Modifier == CKeyFlagsEnum::Shift || Modifier == CKeyFlagsEnum::Ctrl ||
         Modifier == CKeyFlagsEnum::Alt);
}

} // namespace NSKernel
} // namespace NSApplication
