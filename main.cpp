#include "ExceptionHandler.h"
#include <QApplication>

#include "Qt/MainWindow.h"

int main(int argc, char* argv[]) {
  namespace NSApp = NSApplication;
  namespace ns = NSApp::NSQt;
  QApplication QAppLoop(argc, argv);
  ns::MainWindow w;
  w.show();
  try {
    // Initialize Application object
  } catch (...) {
    NSApp::CExceptionHandler React;
    return 0;
  }
  return QAppLoop.exec();
}
