#ifndef NSAPPLICATION_NSKEYBOARD_CLABELMAKER_H
#define NSAPPLICATION_NSKEYBOARD_CLABELMAKER_H

#include "KeyID.h"
#include "KeyTextData.h"
#include <QChar>

namespace NSApplication {
namespace NSKeyboard {

class CLabelMaker {
public:
  static CLabelData make(CKeyID Key);

private:
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CLABELMAKER_H
