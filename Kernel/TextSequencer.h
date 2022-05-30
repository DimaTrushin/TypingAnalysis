#ifndef NSAPPLICATION_NSKERNEL_CTEXTSEQUENCER_H
#define NSAPPLICATION_NSKERNEL_CTEXTSEQUENCER_H

#include "Library/StlExtension/HeapWithAccess.h"
#include "ModifiersTextData.h"
#include "TextDataTree.h"
#include "UniversalTextSequencer.h"

namespace NSApplication {
namespace NSKernel {

namespace NSTextSequencerDetail {

using CFirstPressedHeap =
    NSLibrary::CHeapWithAccess<CUniversalTextSequencer,
                               CUniversalTextSequencer::CFirstPressedOnTop>;

class CTextSequencerBase {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CFirstPressedHeap = NSTextSequencerDetail::CFirstPressedHeap;

public:
  template<class... TArgs>
  CTextSequencerBase(TArgs&&... args);
  template<class TArg1, class... TArgs>
  CTextSequencerBase(TArg1&& arg1, TArgs&&... args)
      : CTextSequencerBase(std::forward<TArgs>(args)...) {
    if (arg1.isValid())
      Sequencers_.push(std::forward<TArg1>(arg1));
  }
  template<class TArg1>
  CTextSequencerBase(TArg1&& arg1) {
    if (arg1.isValid())
      Sequencers_.push(std::forward<TArg1>(arg1));
  }
  template<class TArg1>
  void push(TArg1&& arg1) {
    if (arg1.isValid())
      Sequencers_.push(std::forward<TArg1>(arg1));
  }

  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  CKeyPosition getPosition() const;
  QChar getSymbol() const;
  CTime getPressingTime() const;
  CTime getReleasingTime() const;
  bool isAutoRepeat() const;

private:
  CFirstPressedHeap Sequencers_;
};

} // namespace NSTextSequencerDetail

class CFullTextSequencer : public NSTextSequencerDetail::CTextSequencerBase {
  using CBase = NSTextSequencerDetail::CTextSequencerBase;

public:
  CFullTextSequencer(const CTextDataTree& TextTree,
                     const CModifiersTextData& Modifiers, CTextMode mode);

private:
  void AddModifier(const CModifierData& Modifier, EModifierMode mode);
};

class CPrintedTextSequencer : public NSTextSequencerDetail::CTextSequencerBase {
  using CBase = NSTextSequencerDetail::CTextSequencerBase;

public:
  CPrintedTextSequencer(const CTextDataTree& TextTree,
                        const CModifiersTextData& Modifiers, CTextMode mode);

private:
  void AddModifier(const CModifierData& Modifier, EModifierMode mode);
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CTEXTSEQUENCER_H
