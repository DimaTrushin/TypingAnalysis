#ifndef NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
#define NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H

#include "KeyTextData.h"
#include "Keyboard/KeyID.h"
#include "Keyboard/KeyPosition.h"
#include "TimeApp.h"

#include <QChar>
#include <QObject>
#include <QString>

#include <string>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing {
  CTime Time;
  CKeyPosition KeyPosition;
  CKeyID KeyID;
  QChar KeyLabel;
  QString KeyText;
};

struct CKeyReleasing {
  CTime Time;
  CKeyPosition KeyPosition;
  CKeyID KeyID;
};

} // namespace NSKeyboard
} // namespace NSApplication

// This macro is required to use the CRawKeyEvent class in Qt message system
Q_DECLARE_METATYPE(NSApplication::NSKeyboard::CKeyPressing);
Q_DECLARE_METATYPE(NSApplication::NSKeyboard::CKeyReleasing);
#endif // NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
