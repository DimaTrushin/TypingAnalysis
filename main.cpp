#include "Qt/MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  namespace ns = NSApplication::NSQt;
  QApplication QAppLoop(argc, argv);
  ns::MainWindow w;
  w.show();
  try {
    // Initialize Application object
  } catch (...) {
    // Initialize Exception catcher
    return 0;
  }
  return QAppLoop.exec();
}
