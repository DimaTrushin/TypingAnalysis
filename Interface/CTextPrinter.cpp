#include "CTextPrinter.h"

#include <QTextEdit>

namespace NSApplication {
namespace NSInterface {

namespace NSTextPrinterDetail {

CTextPrinterImpl::CTextPrinterImpl(QTextEdit* TextEdit)
    : TextEdit_(TextEdit),
      TextDataInput_([this](const CTextData& data) { handleTextData(data); }) {
  assert(TextEdit_);
  setDefaultBackgroundColor();
}

CTextPrinterImpl::CTextDataObserver* CTextPrinterImpl::textDataInput() {
  return &TextDataInput_;
}

void CTextPrinterImpl::handleTextData(const CTextData& data) {
  // Preliminary implementation
  switch (data.TextMode.TextMode) {
  case ETextMode::Raw:
    printFormattedSession(data.Session);
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
  buffer_.clear();
  for (const auto& element : Session) {
    if (element.isTrackableSpecial()) {
      assert(element.getLabel().Size > 0);
      buffer_.push_back(element.getLabel().LowSymbol);
    } else {
      for (unsigned char i = 0; i < element.getTextSize(); ++i)
        buffer_.push_back(element.getSymbol(i));
    }
  }
  TextEdit_->setPlainText(QString(buffer_.data(), buffer_.size()));
}

void CTextPrinterImpl::printFormattedSession(const CSession& Session) {
  clear();
  if (Session.empty())
    return;
  buffer_.clear();
  auto iter = Session.cbegin();
  auto sentinel = Session.cend();
  EKeyStatus CurrentStatus = EKeyStatus::MainText;
  while (CurrentStatus != EKeyStatus::End) {
    EKeyStatus NewStatus = extractToBuffer(CurrentStatus, sentinel, &iter);
    printBuffer(CurrentStatus);
    CurrentStatus = NewStatus;
  }
}

void CTextPrinterImpl::printFullText(const CTextDataTree& TextTree) {
  buffer_.clear();
  for (auto iter = TextTree->beginFullText(); iter != TextTree->endFullText();
       ++iter) {
    buffer_.push_back(iter->getSymbol());
  }
  // TO DO
  // If I use setPlainText function sometimes the color changes randomly
  clear();
  printBuffer(Palette_.Text[EKeyStatus::MainText],
              Palette_.Back[EKeyStatus::MainText]);
}

void CTextPrinterImpl::printPrintedText(const CTextDataTree& TextTree) {
  buffer_.clear();
  for (auto iter = TextTree->beginPrintedText();
       iter != TextTree->endPrintedText(); ++iter) {
    buffer_.push_back(iter->getSymbol());
  }
  // TO DO
  // If I use setPlainText function sometimes the color changes randomly
  clear();
  printBuffer(Palette_.Text[EKeyStatus::MainText],
              Palette_.Back[EKeyStatus::MainText]);
}

CTextPrinterImpl::EKeyStatus
CTextPrinterImpl::getKeyStatus(const CKeyEvent& Key) {
  if (Key.isBackspace())
    return EKeyStatus::Backspace;
  if (Key.isTrackableSpecial())
    return EKeyStatus::Control;
  if (Key.getTextSize() > 0)
    return EKeyStatus::MainText;
  return EKeyStatus::Ignore;
}

CTextPrinterImpl::EKeyStatus
CTextPrinterImpl::extractToBuffer(EKeyStatus Status,
                                  const CConstSessionIterator sentinel,
                                  CConstSessionIterator* pIter) {
  auto& iter = *pIter;
  buffer_.clear();
  while (iter != sentinel && (getKeyStatus(*iter) == Status ||
                              getKeyStatus(*iter) == EKeyStatus::Ignore)) {
    switch (Status) {
    case EKeyStatus::MainText:
      for (unsigned char i = 0; i < iter->getTextSize(); ++i)
        buffer_.push_back(iter->getSymbol(i));
      break;
    case EKeyStatus::Backspace:
    case EKeyStatus::Control:
      buffer_.push_back(iter->getLabel().LowSymbol);
      break;
    default:
      break;
    }
    ++iter;
  }
  if (iter == sentinel)
    return EKeyStatus::End;
  return getKeyStatus(*iter);
}

void CTextPrinterImpl::printBuffer(EKeyStatus Status) {
  switch (Status) {
  case EKeyStatus::MainText:
    printBuffer(Palette_.Text[EKeyStatus::MainText],
                Palette_.Back[EKeyStatus::MainText]);
    break;
  case EKeyStatus::Backspace:
    printBuffer(Palette_.Text[EKeyStatus::Backspace],
                Palette_.Back[EKeyStatus::Backspace]);
    break;
  case EKeyStatus::Control:
    printBuffer(Palette_.Text[EKeyStatus::Control],
                Palette_.Back[EKeyStatus::Control]);
    break;
  default:
    break;
  }
}

void CTextPrinterImpl::printBuffer(QColor Text, QColor Back) {
  auto TextColor = TextEdit_->textColor();
  auto BackColor = TextEdit_->textBackgroundColor();
  TextEdit_->setTextColor(Text);
  TextEdit_->setTextBackgroundColor(Back);
  TextEdit_->insertPlainText(QString(buffer_.data(), buffer_.size()));
  TextEdit_->setTextBackgroundColor(BackColor);
  TextEdit_->setTextColor(TextColor);
}

void CTextPrinterImpl::clear() {
  TextEdit_->clear();
}

void CTextPrinterImpl::setDefaultBackgroundColor() {
  QPalette palette;
  QBrush brush(Palette_.Back[EKeyStatus::MainText]);
  brush.setStyle(Qt::SolidPattern);
  palette.setBrush(QPalette::Active, QPalette::Base, brush);
  palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
  TextEdit_->setTextBackgroundColor(Palette_.Back[EKeyStatus::MainText]);
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
