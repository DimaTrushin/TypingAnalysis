#include "ExceptionHandler.h"
#include "Application.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  namespace NSApp = NSApplication;
  QApplication QAppLoop(argc, argv);
  try {
    NSApp::CApplication Application;
    QAppLoop.exec();
  } catch (...) {
    NSApp::CExceptionHandler React;
  }
  return 0;
}
