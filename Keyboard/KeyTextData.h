#ifndef NSAPPLICATION_NSKEYBOARD_CKEYTEXTDATA_H
#define NSAPPLICATION_NSKEYBOARD_CKEYTEXTDATA_H

#include <QChar>

namespace NSApplication {
namespace NSKeyboard {

struct CLabelData {
  QChar LowSymbol;
  QChar HighSymbol;
  unsigned char Size;
};

struct CKeyTextData {
  QChar Symbol[2];
  unsigned char Size;
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYTEXTDATA_H
