#include "TextPrinter.h"

#include <type_traits>

#include <QDebug>
#include <QTextEdit>

namespace NSApplication {
namespace NSInterface {

bool operator==(CTextPalette::CStatusData lhs, CTextPalette::CStatusData rhs) {
  return lhs.Status == rhs.Status && lhs.Depth == rhs.Depth;
}

bool operator!=(CTextPalette::CStatusData lhs, CTextPalette::CStatusData rhs) {
  return !(lhs == rhs);
}

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
  auto iter = Session.cbegin();
  auto sentinel = Session.cend();
  QTextDocument* Doc = getDefaultDocument();
  QTextEdit tmpEdit;
  tmpEdit.setDocument(Doc);

  EKeyStatus CurrentStatus = getKeyRawStatus(*iter);
  while (CurrentStatus != EKeyStatus::End) {
    EKeyStatus NewStatus = extractToBufferRaw(CurrentStatus, sentinel, &iter);
    setFormat({CurrentStatus, 0}, &tmpEdit);
    insertTextFromBuffer(&tmpEdit);
    CurrentStatus = NewStatus;
  }
  TextEdit_->setDocument(Doc);
}

template<class TText>
void CTextPrinterImpl::printFormattedText(const TText& TextView) {
  if (TextView.size() == 0) {
    clear();
    return;
  }
  auto iter = TextView.cbegin();
  auto sentinel = TextView.cend();
  QTextDocument* Doc = getDefaultDocument();
  QTextEdit tmpEdit;
  tmpEdit.setDocument(Doc);

  CStatusData CurrentStatus = getKeyTextStatus(*iter);
  while (CurrentStatus.Status != EKeyStatus::End) {
    CStatusData NewStatus = extractToBufferText(CurrentStatus, sentinel, &iter);
    setFormat(CurrentStatus, &tmpEdit);
    insertTextFromBuffer(&tmpEdit);
    CurrentStatus = NewStatus;
  }
  TextEdit_->setDocument(Doc);
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

CTextPrinterImpl::CStatusData
CTextPrinterImpl::getKeyTextStatus(const CTextNode& TextNode) {
  switch (TextNode.getSymbolStatus()) {
  case ESymbolStatus::TextSymbol:
    return {EKeyStatus::MainText, TextNode.getDepth()};
    break;
  case ESymbolStatus::DeletedSymbolAccidental:
    return {EKeyStatus::AccidentallyDeleted, TextNode.getDepth()};
    break;
  case ESymbolStatus::DeletedSymbolRequired:
    return {EKeyStatus::RequiredDeletion, TextNode.getDepth()};
    break;
  case ESymbolStatus::ErroneousSymbol:
    return {EKeyStatus::Erroneous, TextNode.getDepth()};
    break;
  default:
    assert(false);
    return {EKeyStatus::Ignore, TextNode.getDepth()};
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
CTextPrinterImpl::CStatusData CTextPrinterImpl::extractToBufferText(
    CStatusData Status, const CConstIterator sentinel, CConstIterator* pIter) {
  auto& iter = *pIter;
  buffer_.clear();
  while (iter != sentinel && getKeyTextStatus(*iter) == Status) {
    buffer_.push_back(iter->getSymbol());
    ++iter;
  }
  qDebug() << "buffer_.size() = " << buffer_.size();
  if (iter == sentinel)
    return {EKeyStatus::End, 0};
  return getKeyTextStatus(*iter);
}

void CTextPrinterImpl::setFormat(CStatusData Status,
                                 QTextEdit* pTextEdit) const {
  pTextEdit->setTextBackgroundColor(
      shade(Palette_.Back[Status.Status], Status.Depth));
  pTextEdit->setTextColor(Palette_.Text[Status.Status]);
}

void CTextPrinterImpl::insertTextFromBuffer(QTextEdit* pTextEdit) const {
  pTextEdit->insertPlainText(QString(buffer_.data(), int(buffer_.size())));
}

void CTextPrinterImpl::clear() {
  TextEdit_->clear();
}

void CTextPrinterImpl::setDefaultBackgroundColor() {
  TextEdit_->setTextBackgroundColor(Palette_.Back[EKeyStatus::MainText]);
}

QColor CTextPrinterImpl::shade(QColor Color, unsigned char Depth) {
  int h, s, l;
  Depth = std::min<unsigned char>(Depth, 10);
  Color.getHsv(&h, &s, &l);
  l = (l > 15 * Depth ? l - 15 * Depth : 0);
  return QColor::fromHsv(h, s, l);
}

QTextDocument* CTextPrinterImpl::getDefaultDocument() const {
  QTextDocument* Doc = new QTextDocument(TextEdit_);
  QFont t;
  t.setPointSize(14);
  Doc->setDefaultFont(t);
  return Doc;
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
