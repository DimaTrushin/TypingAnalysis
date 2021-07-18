#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYTEXTMAKER_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYTEXTMAKER_H

#include "KeyMapper.h"
#include "Keyboard/KeyTextData.h"

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

  CKeyTextData getText(CVKCode VK, CKeyShifters Shifters, HKL Layout);
  CLabelData getLabel(USHORT MakeCode, USHORT Flags, HKL Layout);

private:
  bool isLayoutChanged(HKL Layout) const;
  void switchLayout(HKL Layout);
  CKeyTextData getKeyTextData(CVKCode VK, CKeyShifters Shifters);
  CKeyTextData getKeyTextDataWithDeadKey(CVKCode VK, CKeyShifters Shifters);
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
