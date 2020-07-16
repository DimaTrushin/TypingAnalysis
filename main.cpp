#include "ExceptionHandler.h"
#include "Application.h"
#include "Qt/QtLoopExceptionHandler.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  namespace NSApp = NSApplication;
  namespace NSQt = NSApp::NSQt;
  QApplication QAppLoop(argc, argv);
  NSQt::CQtLoopExceptionHandler Handler;
  try {
    NSApp::CApplication Application;
    QAppLoop.exec();
  } catch (...) {
    NSApp::CExceptionHandler React;
  }
  return 0;
}
