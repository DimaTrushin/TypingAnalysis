#include "Application.h"

#include "ExceptionHandler.h"
#include "QtLoopException.h"

#include <QApplication>


int main(int argc, char* argv[]) {
  namespace NSApp = NSApplication;
  QApplication QAppLoop(argc, argv);
  NSApp::CQtLoopExceptionInit LoopExceptions;

  try {
    NSApp::CApplication Application;
    QAppLoop.exec();
  } catch (...) {
    NSApp::CExceptionHandler React;
  }
  return 0;
}
