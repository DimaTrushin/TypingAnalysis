#include "TextPrinter.h"

#include "AppDebug/PerformanceLogger.h"

#include <QPlainTextEdit>
#include <QTextEdit>

#include <QDebug>

namespace NSApplication {
namespace NSInterface {

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
    // Debugger dies here. Do not know what is the issue.
    TextEdit_->setDocument(Text_.get());
  }
}

CTextPrinterImpl::CQTextDocUptr
CTextPrinterImpl::makeText(const CTextData& data) {
  CQTextDocUptr Doc;
  switch (data.textMode()) {
  case ETextMode::Raw:
    Doc = makeFormattedText(data.sessionSequencer());
    break;
  case ETextMode::Full:
    Doc = makeFormattedText(data.fullTextSequencer());
    break;
  case ETextMode::Printed:
    Doc = makeFormattedText(data.printedTextSequencer());
    break;
  default:
    assert(false);
  }
  return Doc;
}

template<class TSequencer>
CTextPrinterImpl::CQTextDocUptr
CTextPrinterImpl::makeFormattedText(TSequencer Sequencer) {
  CQTextDocUptr Doc = getDefaultDocUptr();
  if (!Sequencer.isValid())
    return Doc;

  QTextCursor Cursor = QTextCursor(Doc.get());
  CStatusData CurrentStatus = Sequencer.getStatusData();
  while (CurrentStatus.Status != EKeyStatus::End) {
    CStatusData NewStatus = extractToBuffer(CurrentStatus, &Sequencer);
    setFormat(CurrentStatus, &Cursor);
    insertTextFromBuffer(&Cursor);
    CurrentStatus = NewStatus;
  }
  return Doc;
}

template<class TSequencer>
CTextPrinterImpl::CStatusData
CTextPrinterImpl::extractToBuffer(CStatusData StatusData,
                                  TSequencer* pSequencer) {
  auto& Sequencer = *pSequencer;
  buffer_.clear();
  while (Sequencer.isValid() && (Sequencer.getStatusData() == StatusData ||
                                 Sequencer.getStatus() == EKeyStatus::Ignore)) {
    buffer_.push_back(Sequencer.getSymbol());
    Sequencer.next();
  }
  return Sequencer.getStatusData();
}

void CTextPrinterImpl::setFormat(CStatusData Status,
                                 QTextCursor* pTextCursor) const {
  QTextCharFormat Format;
  switch (Status.Status) {
  case EKeyStatus::Control:
    Format.setForeground(QBrush(Status.Depth == 0 ? Palette_.Text[Status.Status]
                                                  : Palette_.Marker));
    Format.setBackground(QBrush(shade(Palette_.Back[Status.Status], 0)));
    break;
  default:
    Format.setForeground(QBrush(Palette_.Text[Status.Status]));
    Format.setBackground(
        QBrush(shade(Palette_.Back[Status.Status], Status.Depth)));
  }
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
  l = (l > 20 * Depth ? l - 20 * Depth : 0);
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
