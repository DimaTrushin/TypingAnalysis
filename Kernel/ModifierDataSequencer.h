#ifndef NSAPPLICATION_NSKERNEL_CMODIFIERDATASEQUENCER_H
#define NSAPPLICATION_NSKERNEL_CMODIFIERDATASEQUENCER_H

#include "KeyStatus.h"
#include "ModifiersTextData.h"

namespace NSApplication {
namespace NSKernel {

class CModifierNonSequencer {
public:
  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  QChar getSymbol() const;
  CTime getTime() const;
};

class CModifierEssentialSequencer {
  using CIterator = CModifierData::const_iterator;

public:
  CModifierEssentialSequencer(const CIterator& begin, const CIterator& end,
                              ETextMode mode);

  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  QChar getSymbol() const;
  CTime getTime() const;

private:
  CIterator Current_;
  CIterator End_;
  const ETextMode Mode_;
};

class CModifierAllSequencer {
  using CIterator = CModifierData::const_iterator;

public:
  CModifierAllSequencer(const CIterator& begin, const CIterator& end,
                        ETextMode mode);

  bool isValid() const;
  void next();
  EKeyStatus getStatus() const;
  unsigned char getDepth() const;
  CStatusData getStatusData() const;
  QChar getSymbol() const;
  CTime getTime() const;

private:
  CIterator Current_;
  CIterator End_;
  const ETextMode Mode_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMODIFIERDATASEQUENCER_H
