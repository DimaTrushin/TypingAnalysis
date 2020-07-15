#ifndef NSAPPLICATION_CAPPLICATION_H
#define NSAPPLICATION_CAPPLICATION_H

#include <memory>

namespace NSApplication {

class CApplicationImpl;

class CApplication {
public:
  CApplication();
  ~CApplication();
private:
  std::unique_ptr<CApplicationImpl> AppImpl_;
};

} // NSApplication

#endif // NSAPPLICATION_CAPPLICATION_H
