#include "CTextPrinter.h"

#include <type_traits>

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
    printFormattedText(data.textConstFullView());
    break;
  case ETextMode::Printed:
    printFormattedText(data.textConstPrintedView());
    break;
  default:
    assert(false);
  }
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
  EKeyStatus CurrentStatus = getKeyRawStatus(*iter);
  while (CurrentStatus != EKeyStatus::End) {
    EKeyStatus NewStatus = extractToBufferRaw(CurrentStatus, sentinel, &iter);
    Text.append(coloredTextFromBuffer(CurrentStatus));
    CurrentStatus = NewStatus;
  }
  TextEdit_->setHtml(Text);
}

template<class TText>
void CTextPrinterImpl::printFormattedText(const TText& TextView) {
  using const_iterator = typename TText::const_iterator;
  const_iterator iter;
  const_iterator sentinel;
  if (TextView.size() == 0) {
    clear();
    return;
  }
  iter = TextView.begin();
  sentinel = TextView.end();
  QString Text;
  EKeyStatus CurrentStatus = getKeyTextStatus(*iter);
  while (CurrentStatus != EKeyStatus::End) {
    EKeyStatus NewStatus = extractToBufferText(CurrentStatus, sentinel, &iter);
    Text.append(coloredTextFromBuffer(CurrentStatus));
    CurrentStatus = NewStatus;
  }
  TextEdit_->setHtml(Text);
}

CTextPrinterImpl::EKeyStatus
CTextPrinterImpl::getKeyRawStatus(const CKeyEvent& Key) {
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
CTextPrinterImpl::getKeyTextStatus(const CTextNode& TextNode) {
  switch (TextNode.getSymbolStatus()) {
  case ESymbolStatus::TextSymbol:
    return EKeyStatus::MainText;
    break;
  case ESymbolStatus::DeletedSymbolAccidental:
    return EKeyStatus::AccidentallyDeleted;
    break;
  case ESymbolStatus::DeletedSymbolRequired:
    return EKeyStatus::RequiredDeletion;
    break;
  case ESymbolStatus::ErroneousSymbol:
    return EKeyStatus::Erroneous;
    break;
  default:
    return EKeyStatus::Ignore;
    break;
  }
}

CTextPrinterImpl::EKeyStatus
CTextPrinterImpl::extractToBufferRaw(EKeyStatus Status,
                                     const CConstSessionIterator sentinel,
                                     CConstSessionIterator* pIter) {
  auto& iter = *pIter;
  buffer_.clear();
  while (iter != sentinel && (getKeyRawStatus(*iter) == Status ||
                              getKeyRawStatus(*iter) == EKeyStatus::Ignore)) {
    switch (Status) {
    case EKeyStatus::MainText:
      assert(iter->getTextSize() > 0);
      buffer_.push_back(iter->getLastSymbol());
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
  return getKeyRawStatus(*iter);
}
template<class CConstIterator>
CTextPrinterImpl::EKeyStatus CTextPrinterImpl::extractToBufferText(
    EKeyStatus Status, const CConstIterator sentinel, CConstIterator* pIter) {
  auto& iter = *pIter;
  buffer_.clear();
  while (iter != sentinel && (getKeyTextStatus(*iter) == Status ||
                              getKeyTextStatus(*iter) == EKeyStatus::Ignore)) {
    buffer_.push_back(iter->getSymbol());
    ++iter;
  }
  qDebug() << "buffer_.size() = " << buffer_.size();
  if (iter == sentinel)
    return EKeyStatus::End;
  return getKeyTextStatus(*iter);
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
  if (Status < EKeyStatus::Ignore) {
    Text = coloredTextFromBuffer(Palette_.Text[Status], Palette_.Back[Status]);
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

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
