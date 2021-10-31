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
  if (Session.empty()) {
    clear();
    return;
  }
  buffer_.clear();
  auto iter = Session.cbegin();
  auto sentinel = Session.cend();
  QString Text;
  EKeyStatus CurrentStatus = getKeyStatus(*iter);
  while (CurrentStatus != EKeyStatus::End) {
    EKeyStatus NewStatus = extractToBuffer(CurrentStatus, sentinel, &iter);
    Text.append(coloredTextFromBuffer(CurrentStatus));
    CurrentStatus = NewStatus;
  }
  TextEdit_->setHtml(Text);
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
  if (Key.isSilentDeadKey())
    return EKeyStatus::SilentDeadKey;
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
      assert(iter->getTextSize() > 0);
      buffer_.push_back(iter->getSymbol(iter->getTextSize() - 1));
      break;
    case EKeyStatus::Backspace:
    case EKeyStatus::Control:
    case EKeyStatus::SilentDeadKey:
      buffer_.push_back(iter->getLabel().LowSymbol);
      break;
    default:
      break;
    }
    ++iter;
  }
  qDebug() << "buffer_.size() = " << buffer_.size();
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
  auto Anchor = CColorAnchor(Text, Back, TextEdit_);
  TextEdit_->insertPlainText(QString(buffer_.data(), buffer_.size()));
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

QString CTextPrinterImpl::coloredTextFromBuffer(EKeyStatus Status) {
  QString Text;
  switch (Status) {
  case EKeyStatus::MainText:
    Text = coloredTextFromBuffer(Palette_.Text[EKeyStatus::MainText],
                                 Palette_.Back[EKeyStatus::MainText]);
    break;
  case EKeyStatus::Backspace:
    Text = coloredTextFromBuffer(Palette_.Text[EKeyStatus::Backspace],
                                 Palette_.Back[EKeyStatus::Backspace]);
    break;
  case EKeyStatus::Control:
    Text = coloredTextFromBuffer(Palette_.Text[EKeyStatus::Control],
                                 Palette_.Back[EKeyStatus::Control]);
    break;
  case EKeyStatus::SilentDeadKey:
    Text = coloredTextFromBuffer(Palette_.Text[EKeyStatus::SilentDeadKey],
                                 Palette_.Back[EKeyStatus::SilentDeadKey]);
    break;
  default:
    break;
  }
  return Text;
}

QString CTextPrinterImpl::coloredTextFromBuffer(QColor Text, QColor Back) {

  return QString("<span "
                 "style=\"color:rgb(%1,%2,%3);background-color:rgb(%4,%5,%6);"
                 "\">%7</span>")
      .arg(Text.red())
      .arg(Text.green())
      .arg(Text.blue())
      .arg(Back.red())
      .arg(Back.green())
      .arg(Back.blue())
      .arg(QString(buffer_.data(), buffer_.size()));
}

CTextPrinterImpl::CColorAnchor::CColorAnchor(QColor Text, QColor Back,
                                             QTextEdit* TextEdit)
    : OldText_(TextEdit->textColor()),
      OldBack_(TextEdit->textBackgroundColor()), TextEdit_(TextEdit) {
  assert(TextEdit_);
  TextEdit_->setTextColor(Text);
  TextEdit_->setTextBackgroundColor(Back);
}

CTextPrinterImpl::CColorAnchor::~CColorAnchor() {
  TextEdit_->setTextBackgroundColor(OldBack_);
  TextEdit_->setTextColor(OldText_);
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication