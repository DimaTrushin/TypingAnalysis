#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYMAPPER_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYMAPPER_H

#include "KeyShifters.h"
#include "VkCode.h"

#include <QChar>

#include <Windows.h>
#include <array>
#include <map>
#include <optional>

namespace NSApplication {
namespace NSKeyboard {
namespace NSWindows {

namespace NSKeyMapperDetail {

struct CKeyData {
  CVKCode VK;
  CKeyShifters Shifters;

  friend bool operator<(const CKeyData& first, const CKeyData& second) {
    if (first.VK < second.VK)
      return true;
    if (first.VK > second.VK)
      return false;
    return first.Shifters < second.Shifters;
  }
};

struct CKeyInfo {
  QChar Character = QChar();
  bool isDeadKey = false;
};

class CSimpleKeyMapper {
public:
  using QCharOptional = std::optional<QChar>;
  CSimpleKeyMapper(HKL hkl); // create a Mapper for a given layout
  QCharOptional getSymbol(CVKCode VK, CKeyShifters Shifters) const;
  bool isDeadKey(CVKCode VK, CKeyShifters Shifters) const;
  bool hasSymbol(CVKCode VK, CKeyShifters Shifters) const;
  bool isControl(CVKCode VK, CKeyShifters Shifters) const;
  bool isMapped(CVKCode VK) const;
  HKL getLayout() const;

  static bool isControlChar(QChar Char);

protected:
  void setBaseCharacterTable();
  void handleKey(CVKCode VK);
  void handleKeyWithShifters(CVKCode VK, CKeyShifters Shifters);

  bool isSynthetic(CVKCode VK) const;

  static bool isControl(CKeyShifters Shifters, QChar Char);

  static constexpr const QChar UndefinedQChar_ = QChar();

  const HKL Layout_;
  std::map<CKeyData, CKeyInfo> KeyTable_;
};

class CKeySequenceMapper : public CSimpleKeyMapper {
  using CBase = CSimpleKeyMapper;

public:
  CKeySequenceMapper(HKL Layout);
  QCharOptional getCombinedSymbol(CVKCode DeadVK, CKeyShifters DeadShifters,
                                  CVKCode VK, CKeyShifters Shifters) const;
  bool areCompatible(CVKCode DeadVK, CKeyShifters DeadShifters, CVKCode VK,
                     CKeyShifters Shifters) const;

private:
  void setCompatiblePairs();
  void fillCompatiblePairsForKey(const CKeyData& DeadKey);
  void addIfCompatible(const CKeyData& DeadKey, const CKeyData& NextKey,
                       QChar NextChar);

  std::map<std::pair<CKeyData, CKeyData>, QChar> KeyPairTable_;
};
} // namespace NSKeyMapperDetail

using CKeyMapper = NSKeyMapperDetail::CKeySequenceMapper;

} // namespace NSWindows
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CKEYMAPPER_H
