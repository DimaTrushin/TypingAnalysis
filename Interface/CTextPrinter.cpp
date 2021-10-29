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
  //  printSession(data.Session);
  printTextTree(data.TextTree);
}

void CTextPrinterImpl::printSession(const CSession& Session) {
  // Debug version of the code
  QString Text;
  for (const auto& element : Session) {
    Text.push_back(
        QString(element.getTextData().Symbol, element.getTextData().Size));
  }
  TextEdit_->setPlainText(Text);
}

void CTextPrinterImpl::printTextTree(const CTextDataTree& TextTree) {
  QString Text;
  //  for (auto iter = TextTree->beginFullText(); iter !=
  //  TextTree->endFullText();
  //       ++iter) {
  //    Text.push_back(iter->getSymbol());
  //  }
  for (auto iter = TextTree->beginPrintedText();
       iter != TextTree->endPrintedText(); ++iter) {
    Text.push_back(iter->getSymbol());
  }
  TextEdit_->setPlainText(Text);
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
