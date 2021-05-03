#ifndef NSAPPLICATION_NSKEYBOARD_NSLINUX_CKEYBOARDLISTENERLIN_H
#define NSAPPLICATION_NSKEYBOARD_NSLINUX_CKEYBOARDLISTENERLIN_H

#include "Keyboard/AnyKeyboardKiller.h"

#include <QObject>
#include <future>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing;
struct CKeyReleasing;

class CKeyboardHandler;

namespace NSLinux {

class CKeyboardListenerLinImpl : public QObject {
  Q_OBJECT

  friend class CKiller;

public:
  using CAnyKillerPromise = std::promise<CAnyKeyboardKiller>;
  CKeyboardListenerLinImpl(CAnyKillerPromise, CKeyboardHandler*);
  ~CKeyboardListenerLinImpl();

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

} // namespace NSLinux
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSLINUX_CKEYBOARDLISTENERLIN_H
