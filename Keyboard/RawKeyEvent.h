#ifndef NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
#define NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H

#include <QObject>
#include <string>


namespace NSApplication {
namespace NSKeyboard {

// This is a dummy version of CRawKeyEvent
// TO DO
class CRawKeyEvent {
public:
  CRawKeyEvent() = default;
  CRawKeyEvent(const char* text);
  std::string Text;
};

} // NSKeyboard
} // NSApplication

// This macro is required to use the CRawKeyEvent class in Qt message system
Q_DECLARE_METATYPE(NSApplication::NSKeyboard::CRawKeyEvent);

#endif // NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
