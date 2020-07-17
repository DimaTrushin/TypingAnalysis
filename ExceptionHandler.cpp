#include "ExceptionHandler.h"

#include <exception>
#include <QMessageBox>


namespace NSApplication {

CExceptionHandler::CExceptionHandler() {
  QMessageBox MessageBox;
  MessageBox.setIcon(QMessageBox::Critical);
  MessageBox.setWindowTitle(kExceptionWindowsTitle_);
  try {
    throw;
  } catch (std::exception& exception) {
    MessageBox.setText(exception.what());
  } catch (...) {
    MessageBox.setText(kUnknownExceptionMsg_);
  }
  MessageBox.exec();
}
} // NSApplication
