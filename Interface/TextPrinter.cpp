#include "TextPrinter.h"

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
  switch (data.textMode()) {
  case ETextMode::Raw:
    printFormattedText(data.rawSession());
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

template<class TNode>
CTextPrinterImpl::CStatusData
CTextPrinterImpl::getStatus(const TNode& TextNode) const {
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

template<>
CTextPrinterImpl::CStatusData
CTextPrinterImpl::getStatus<CTextPrinterImpl::CKeyEvent>(
    const CKeyEvent& Key) const {
  if (Key.isBackspace())
    return {EKeyStatus::Backspace, 0};
  if (Key.isTrackableSpecial())
    return {EKeyStatus::Control, 0};
  if (Key.isSilentDeadKey())
    return {EKeyStatus::SilentDeadKey, 0};
  if (Key.getTextSize() > 0)
    return {EKeyStatus::MainText, 0};
  return {EKeyStatus::Ignore, 0};
}

template<class TConstIterator>
CTextPrinterImpl::CStatusData
CTextPrinterImpl::extractToBuffer(CStatusData StatusData,
                                  const TConstIterator sentinel,
                                  TConstIterator* pIter) {
  auto& iter = *pIter;
  buffer_.clear();
  while (iter != sentinel && getStatus(*iter) == StatusData) {
    buffer_.push_back(iter->getSymbol());
    ++iter;
  }
  qDebug() << "buffer_.size() = " << buffer_.size();
  if (iter == sentinel)
    return {EKeyStatus::End, 0};
  return getStatus(*iter);
}

template<>
CTextPrinterImpl::CStatusData
CTextPrinterImpl::extractToBuffer<CTextPrinterImpl::CSession::const_iterator>(
    CStatusData StatusData, const CSession::const_iterator sentinel,
    CSession::const_iterator* pIter) {
  auto& iter = *pIter;
  buffer_.clear();
  while (iter != sentinel && (getStatus(*iter) == StatusData ||
                              getStatus(*iter).Status == EKeyStatus::Ignore)) {
    switch (StatusData.Status) {
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
    return {EKeyStatus::End, 0};
  return getStatus(*iter);
}

template<class TText>
void CTextPrinterImpl::printFormattedText(const TText& TextView) {
  if (TextView.empty()) {
    clear();
    return;
  }
  auto iter = TextView.cbegin();
  auto sentinel = TextView.cend();
  QTextDocument* Doc = getDefaultDocument();
  QTextEdit tmpEdit;
  tmpEdit.setDocument(Doc);

  CStatusData CurrentStatus = getStatus(*iter);
  while (CurrentStatus.Status != EKeyStatus::End) {
    CStatusData NewStatus = extractToBuffer(CurrentStatus, sentinel, &iter);
    setFormat(CurrentStatus, &tmpEdit);
    insertTextFromBuffer(&tmpEdit);
    CurrentStatus = NewStatus;
  }
  TextEdit_->setDocument(Doc);
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
