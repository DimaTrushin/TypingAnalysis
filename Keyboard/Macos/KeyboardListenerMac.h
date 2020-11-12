#ifndef NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYBOARDLISTENERMAC_H
#define NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYBOARDLISTENERMAC_H

#include "Keyboard/AnyKeyboardKiller.h"

#include <future>
#include <QObject>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing;
struct CKeyReleasing;

class CKeyboardHandler;

namespace NSMacos {

class CKeyboardListenerMacImpl : public QObject {
  Q_OBJECT

  friend class CKiller;
public:
  using CAnyKillerPromise = std::promise<CAnyKeyboardKiller>;
  CKeyboardListenerMacImpl(CAnyKillerPromise, CKeyboardHandler*);
  ~CKeyboardListenerMacImpl();

signals:
  void KeyPressing(const CKeyPressing&);
  void KeyReleasing(const CKeyReleasing&);
public:
  int exec();
private:
  // Implementation details
};


// The object provides a way to shut down the listener
class CKiller {
public:
  CKiller() = default;
  // CKiller(...)
  void stopListener() const;

private:
  // Implementation details
};

} // NSMacos
} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYBOARDLISTENERMAC_H
