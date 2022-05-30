#ifndef NSAPPLICATION_NSKERNEL_CMODIFIERDATASEQUENCER_H
#define NSAPPLICATION_NSKERNEL_CMODIFIERDATASEQUENCER_H

#include "KeyStatus.h"
#include "Keyboard/KeyPosition.h"
#include "ModifiersTextData.h"

namespace NSApplication {
namespace NSKernel {

class CModifierNonSequencer {
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
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
};

class CModifierEssentialSequencer {
  using CIterator = CModifierData::const_iterator;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  CModifierEssentialSequencer(const CIterator& begin, const CIterator& end,
                              ETextMode mode);

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
  CIterator Current_;
  CIterator End_;
  const ETextMode Mode_;
};

class CModifierAllSequencer {
  using CIterator = CModifierData::const_iterator;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  CModifierAllSequencer(const CIterator& begin, const CIterator& end,
                        ETextMode mode);

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
  CIterator Current_;
  CIterator End_;
  const ETextMode Mode_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMODIFIERDATASEQUENCER_H
