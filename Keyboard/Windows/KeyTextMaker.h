#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYTEXTMAKER_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYTEXTMAKER_H

#include "KeyMapper.h"
#include "Keyboard/KeyTextData.h"

#include <QString>

#include <optional>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

class CKeyTextMaker {
  using CKeyData = NSKeyMapperDetail::CKeyData;
  using QCharOptional = CKeyMapper::QCharOptional;

public:
  CKeyTextMaker();

  size_t numberOfMappers() const;

  // TO DO
  // I am not sure that QString is the best thing to return here.
  // I want standard layout data!
  // Need to think on the design.
  QString get(CVKCode VK, CKeyShifters Shifters, HKL Layout);
  QChar getLabel(USHORT MakeCode, USHORT Flags, HKL Layout);

  CKeyTextData get_ext(CVKCode VK, CKeyShifters Shifters, HKL Layout);
  CLabelData getLabel_ext(USHORT MakeCode, USHORT Flags, HKL Layout);

private:
  bool isLayoutChanged(HKL Layout) const;
  void switchLayout(HKL Layout);
  QString getSymbols(CVKCode VK, CKeyShifters Shifters);
  CKeyTextData getKeyTextData(CVKCode VK, CKeyShifters Shifters);
  QString getSymbolsWithDeadKey(CVKCode VK, CKeyShifters Shifters);
  CKeyTextData getKeyTextDataWithDeadKey(CVKCode VK, CKeyShifters Shifters);
  QString getSymbolsPlain(CVKCode VK, CKeyShifters Shifters);
  CKeyTextData getKeyTextDataNoDeadKey(CVKCode VK, CKeyShifters Shifters);
  QCharOptional getPlainSymbol(CVKCode VK, CKeyShifters Shifters) const;
  QCharOptional getCombinedSymbol(CVKCode VK, CKeyShifters Shifters) const;
  QChar getDeadKeySymbol() const;

  const CKeyMapper& CurrentMapper() const;
  const CKeyMapper& Mapper(HKL Layout);
  HKL CurrentLayout() const;
  const CKeyData& DeadKey() const;
  bool hasDeadKeyInBuffer() const;
  bool isDeadKey(CVKCode VK, CKeyShifters Shifters) const;

  std::map<HKL, CKeyMapper> Mappers_;
  std::map<HKL, CKeyMapper>::iterator CurrentMapperIt_;
  std::optional<CKeyData> PreviousDeadKey_;
};

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYTEXTMAKER_H
