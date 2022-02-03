#include "TextPrinter.h"

#include "AppDebug/PerformanceLogger.h"

#include <QPlainTextEdit>
#include <QTextEdit>

#include <QDebug>

namespace NSApplication {
namespace NSInterface {

bool operator==(CTextPalette::CStatusData lhs, CTextPalette::CStatusData rhs) {
  return lhs.Status == rhs.Status && lhs.Depth == rhs.Depth;
}

bool operator!=(CTextPalette::CStatusData lhs, CTextPalette::CStatusData rhs) {
  return !(lhs == rhs);
}

namespace NSTextPrinterDetail {

CTextPrinterImpl::CTextPrinterImpl(QPlainTextEdit* TextEdit)
    : TextEdit_(TextEdit),
      TextDataInput_([this](const CTextData& data) { handleTextData(data); }) {
  assert(TextEdit_);
}

CTextPrinterImpl::~CTextPrinterImpl() = default;

CTextPrinterImpl::CTextDataObserver* CTextPrinterImpl::textDataInput() {
  return &TextDataInput_;
}

void CTextPrinterImpl::handleTextData(const CTextData& data) {
  NSAppDebug::CTimeAnchor Anchor("TextPrinting time =");
  auto TextOpt = Cacher_.find({&data.rawSession(), data.textInfo()});
  if (TextOpt.has_value()) {
    TextEdit_->setDocument(TextOpt->get().get());
    return;
  }
  CTimer Timer;
  Text_ = makeText(data);
  CTime Elapsed = Timer.get();
  if (Elapsed > TimeLimit_) {
    auto Data =
        Cacher_.insert({&data.rawSession(), data.textInfo()}, std::move(Text_));
    assert(Data != nullptr);
    TextEdit_->setDocument(Data->get());
  } else {
    TextEdit_->setDocument(Text_.get());
  }
}

CTextPrinterImpl::CQTextDocUptr
CTextPrinterImpl::makeText(const CTextData& data) {
  CQTextDocUptr Doc;
  switch (data.textMode()) {
  case ETextMode::Raw:
    Doc = makeFormattedText(data.rawSession());
    break;
  case ETextMode::Full:
    Doc = makeFormattedText(data.textConstFullView());
    break;
  case ETextMode::Printed:
    Doc = makeFormattedText(data.textConstPrintedView());
    break;
  default:
    assert(false);
  }
  return Doc;
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
  if (iter == sentinel)
    return {EKeyStatus::End, 0};
  return getStatus(*iter);
}

template<class TText>
CTextPrinterImpl::CQTextDocUptr
CTextPrinterImpl::makeFormattedText(const TText& TextView) {
  CQTextDocUptr Doc = getDefaultDocUptr();
  if (TextView.empty())
    return Doc;
  auto iter = TextView.cbegin();
  auto sentinel = TextView.cend();

  QTextCursor Cursor = QTextCursor(Doc.get());
  CStatusData CurrentStatus = getStatus(*iter);
  while (CurrentStatus.Status != EKeyStatus::End) {
    CStatusData NewStatus = extractToBuffer(CurrentStatus, sentinel, &iter);
    setFormat(CurrentStatus, &Cursor);
    insertTextFromBuffer(&Cursor);
    CurrentStatus = NewStatus;
  }
  return Doc;
}

void CTextPrinterImpl::setFormat(CStatusData Status,
                                 QTextCursor* pTextCursor) const {
  QTextCharFormat Format;
  Format.setForeground(QBrush(Palette_.Text[Status.Status]));
  Format.setBackground(
      QBrush(shade(Palette_.Back[Status.Status], Status.Depth)));
  pTextCursor->setCharFormat(Format);
}

void CTextPrinterImpl::insertTextFromBuffer(QTextCursor* pTextCursor) const {
  pTextCursor->insertText(QString(buffer_.data(), int(buffer_.size())));
}

void CTextPrinterImpl::clear() {
  TextEdit_->clear();
}

QColor CTextPrinterImpl::shade(QColor Color, unsigned char Depth) {
  int h, s, l;
  Depth = std::min<unsigned char>(Depth, 10);
  Color.getHsv(&h, &s, &l);
  l = (l > 15 * Depth ? l - 15 * Depth : 0);
  return QColor::fromHsv(h, s, l);
}

CTextPrinterImpl::CQTextDocUptr CTextPrinterImpl::getDefaultDocUptr() {
  CQTextDocUptr Doc = std::make_unique<QTextDocument>();
  QFont t;
  t.setPointSize(kDefaultFontSize);
  Doc->setDefaultFont(t);
  Doc->setDocumentLayout(new QPlainTextDocumentLayout(Doc.get()));
  return Doc;
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
