#ifndef NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYBOARDLISTENERMAC_H
#define NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYBOARDLISTENERMAC_H

#include "Keyboard/AnyKeyboardKiller.h"

#include <QObject>

#include <future>

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

Q_SIGNALS:
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

} // namespace NSMacos
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYBOARDLISTENERMAC_H
