#include "CTextPrinter.h"

#include <QTextEdit>

namespace NSApplication {
namespace NSInterface {

namespace NSTextPrinterDetail {

CTextPrinterImpl::CTextPrinterImpl(QTextEdit* TextEdit)
    : TextEdit_(TextEdit),
      TextDataInput_([this](const CTextData& data) { handleTextData(data); }) {
  assert(TextEdit_);
}

CTextPrinterImpl::CTextDataObserver* CTextPrinterImpl::textDataInput() {
  return &TextDataInput_;
}

void CTextPrinterImpl::handleTextData(const CTextData& data) {
  // Preliminary implementation
  printSession(data.Session);
}

void CTextPrinterImpl::printSession(const CSession& Session) {
  // Debug version of the code
  QString Text;
  for (const auto& element : Session) {
    Text.push_back(QString(element.getText().Symbol, element.getText().Size));
  }
  TextEdit_->setPlainText(Text);
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
