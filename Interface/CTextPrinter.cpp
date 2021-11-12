#include "CTextPrinter.h"

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
  buffer_.clear();
  auto iter = Session.cbegin();
  auto sentinel = Session.cend();
  QString Text;
  EKeyStatus CurrentStatus = getKeyRawStatus(*iter);
  while (CurrentStatus != EKeyStatus::End) {
    EKeyStatus NewStatus = extractToBufferRaw(CurrentStatus, sentinel, &iter);
    Text.append(coloredTextFromBuffer({CurrentStatus, 0}));
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
  CStatusData CurrentStatus = getKeyTextStatus(*iter);
  while (CurrentStatus.Status != EKeyStatus::End) {
    CStatusData NewStatus = extractToBufferText(CurrentStatus, sentinel, &iter);
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

QString CTextPrinterImpl::coloredTextFromBuffer(CStatusData StatusData) {
  QString Text;
  if (StatusData.Status < EKeyStatus::Ignore) {
    Text = coloredTextFromBuffer(
        Palette_.Text[StatusData.Status],
        shade(Palette_.Back[StatusData.Status], StatusData.Depth));
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

QColor CTextPrinterImpl::shade(QColor Color, unsigned char Depth) {
  int h, s, l;
  Depth = std::min<unsigned char>(Depth, 10);
  Color.getHsv(&h, &s, &l);
  l = (l > 15 * Depth ? l - 15 * Depth : 0);
  return QColor::fromHsv(h, s, l);
}

} // namespace NSTextPrinterDetail

} // namespace NSInterface
} // namespace NSApplication
