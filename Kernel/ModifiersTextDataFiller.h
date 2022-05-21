#ifndef NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATAFILLER_H
#define NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATAFILLER_H

#include "Library/StlExtension/HeapWithAccess.h"
#include "ModifiersTextData.h"
#include "Session.h"
#include "TextDataTree.h"

namespace NSApplication {
namespace NSKernel {

namespace NSModifiersTextDataFillerDetails {

class CPressedModifiers {
  struct CFirstRelease {
    bool operator()(const CModifierData::iterator& lhs,
                    const CModifierData::iterator& rhs) const;
  };
  using CPressedKeys =
      NSLibrary::CHeapWithAccess<CModifierData::iterator, CFirstRelease>;

public:
  void pressKey(CModifierData::iterator it);
  void increaseDependencies(ETextMode mode);
  void releaseBefore(CTime Time);
  void clear();

  bool empty() const;

private:
  CPressedKeys PressedKeys_;
};

} // namespace NSModifiersTextDataFillerDetails

class CModifiersTextDataFiller {
  using CPressedModifiers = NSModifiersTextDataFillerDetails::CPressedModifiers;

public:
  void fill(const CSession& Session, const CTextDataTree& TextTree,
            CModifiersTextData* pData);

private:
  void fillDependencies(const CTextDataTree& TextTree, CModifierData* pData);
  void fillShifts(const CSession& Session, const CTextDataTree& TextTree,
                  CModifierData* pData);
  void fillCtrls(const CSession& Session, const CTextDataTree& TextTree,
                 CModifierData* pData);
  void fillAlts(const CSession& Session, const CTextDataTree& TextTree,
                CModifierData* pData);
  void findShifts(const CSession& Session, CModifierData* pData);
  void findCtrls(const CSession& Session, CModifierData* pData);
  void findAlts(const CSession& Session, CModifierData* pData);

  CPressedModifiers PressedModifiers_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMODIFIERSTEXTDATAFILLER_H
