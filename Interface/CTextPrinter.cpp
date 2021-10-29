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
  switch (data.TextMode.TextMode) {
  case ETextMode::Raw:
    printSession(data.Session);
    break;
  case ETextMode::Full:
    printFullText(data.TextTree);
    break;
  case ETextMode::Printed:
    printPrintedText(data.TextTree);
    break;
  default:
    assert(false);
  }
}

void CTextPrinterImpl::printSession(const CSession& Session) {
  // Debug version of the code
  QString Text;
  for (const auto& element : Session) {
    if (element.isTrackableSpecial()) {
      assert(element.getLabel().Size > 0);
      Text.push_back(element.getLabel().LowSymbol);
    } else {
      Text.push_back(
          QString(element.getTextData().Symbol, element.getTextData().Size));
    }
  }
  TextEdit_->setPlainText(Text);
}

void CTextPrinterImpl::printFullText(const CTextDataTree& TextTree) {
  QString Text;
  for (auto iter = TextTree->beginFullText(); iter != TextTree->endFullText();
       ++iter) {
    Text.push_back(iter->getSymbol());
  }
  TextEdit_->setPlainText(Text);
}

void CTextPrinterImpl::printPrintedText(const CTextDataTree& TextTree) {
  QString Text;
  for (auto iter = TextTree->beginPrintedText();
       iter != TextTree->endPrintedText(); ++iter) {
    Text.push_back(iter->getSymbol());
  }
  TextEdit_->setPlainText(Text);
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
