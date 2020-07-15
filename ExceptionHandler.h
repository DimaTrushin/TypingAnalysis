#ifndef NSAPPLICATION_CEXCEPTIONHANDLER_H
#define NSAPPLICATION_CEXCEPTIONHANDLER_H

namespace NSApplication {

class CExceptionHandler {
public:
  CExceptionHandler();
private:
  static constexpr const char* kUnknownExceptionMsg_ = "Unknown Exception!";
  static constexpr const char* kExceptionWindowsTitle_ = "Exception encountered";
};
} // NSApplication

#endif // NSAPPLICATION_CEXCEPTIONHANDLER_H
