#include "TextData.h"

namespace NSApplication {
namespace NSKernel {

CTextData::CTextData(const CSession& Session, const CTextDataTree& TextTree,
                     const CModifiersTextData& ModifiersData,
                     CTextMode TextMode)
    : Session_(std::cref(Session)), TextTree_(std::cref(TextTree)),
      ModifiersData_(std::cref(ModifiersData)), TextMode_(TextMode) {
}

CTextData::CConstFullTextProxy CTextData::textConstFullView() const {
  return TextTree_.get()->textConstFullView();
}

CTextData::CConstPrintedTextProxy CTextData::textConstPrintedView() const {
  return TextTree_.get()->textConstPrintedView();
}

const CSession& CTextData::rawSession() const {
  return Session_;
}

const CTextDataTree& CTextData::textTree() const {
  return TextTree_;
}

CTextMode CTextData::textInfo() const {
  return TextMode_;
}

ETextMode CTextData::textMode() const {
  return TextMode_.TextMode;
}

EModifierMode CTextData::shiftMode() const {
  return TextMode_.ShiftMode;
}

EModifierMode CTextData::ctrlMode() const {
  return TextMode_.CtrlMode;
}

EModifierMode CTextData::altMode() const {
  return TextMode_.AltMode;
}

CSessionTextSequencer CTextData::sessionSequencer() const {
  return CSessionTextSequencer(rawSession().begin(), rawSession().end());
}

CTextTreeFullSequencer CTextData::fullTextSequencer() const {
  return CTextTreeFullSequencer(textTree()->beginFullText(),
                                textTree()->endFullText());
}

CTextTreePrintedSequencer CTextData::printedTextSequencer() const {
  return CTextTreePrintedSequencer(textTree()->beginPrintedText(),
                                   textTree()->endPrintedText());
}

} // namespace NSKernel
} // namespace NSApplication
