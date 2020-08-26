#ifndef NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
#define NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H

#include "Keyboard/KeyID.h"
#include "Keyboard/KeyPosition.h"
#include "Time.h"

#include <QObject>
#include <QChar>
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

} // NSKeyboard
} // NSApplication

// This macro is required to use the CRawKeyEvent class in Qt message system
Q_DECLARE_METATYPE(NSApplication::NSKeyboard::CKeyPressing);
Q_DECLARE_METATYPE(NSApplication::NSKeyboard::CKeyReleasing);
#endif // NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
