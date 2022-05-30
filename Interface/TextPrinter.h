#ifndef NSAPPLICATION_NSINTERFACE_TEXTPRINTER_H
#define NSAPPLICATION_NSINTERFACE_TEXTPRINTER_H

#include "Kernel/KeyStatus.h"
#include "Kernel/TextData.h"
#include "Kernel/TextDataTree.h"
#include "Kernel/TextModeCacher.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/Cacher.h"
#include "Library/StlExtension/MvcWrappers.h"

#include <QColor>
#include <QPalette>

#include <array>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QPlainTextEdit;
class QTextCursor;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

struct CTextPalette {
  using EKeyStatus = NSKernel::EKeyStatus;

  using CStatusData = NSKernel::CStatusData;

  std::array<QColor, EKeyStatus::End> Text{{
      {0, 0, 0} /*MainText*/,
      {0, 0, 0} /*AccidentallyDeleted*/,
      {0, 0, 0} /*RequiredDeletion*/,
      {180, 0, 0} /*Erroneous*/,
      {180, 0, 0} /*Backspace*/,
      {50, 50, 255} /*Control*/,
      {255, 120, 0} /*EssentialControl*/,
      {180, 0, 0} /*SilentDeadKey*/,
      {0, 0, 0} /*Ignore*/
  }};
  std::array<QColor, EKeyStatus::End> Back{{
      {192, 220, 192} /*MainText*/,
      {255, 180, 180} /*AccidentallyDeleted*/,
      {255, 90, 90} /*RequiredDeletion*/,
      {255, 204, 153} /*Erroneous*/,
      {192, 220, 192} /*Backspace*/,
      {192, 220, 192} /*Control*/,
      {192, 220, 192} /*EssentialControl*/,
      {192, 220, 192} /*SilentDeadKey*/,
      {0, 0, 0} /*Ignore*/
  }};
};

namespace NSTextPrinterDetail {

class CTextPrinterImpl {
  using CTextData = NSKernel::CTextData;
  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CKeyIDEnum = NSKeyboard::CKeyIDEnum;
  using CKeyEvent = NSKernel::CKeyEvent;
  using CSession = NSKernel::CSession;
  using CConstSessionIterator = CSession::const_iterator;
  using CTextDataTree = NSKernel::CTextDataTree;
  using ETextMode = NSKernel::ETextMode;
  using CFullTextIterator = CTextDataTree::CFullTextIterator;
  using CConstFullTextIterator = CTextDataTree::CConstFullTextIterator;
  using CTextIterator = CTextDataTree::CTextIterator;
  using CConstTextIterator = CTextDataTree::CConstTextIterator;

  using CTextNode = NSKernel::CTextNode;

  using EKeyStatus = CTextPalette::EKeyStatus;
  using ESymbolStatus = NSKernel::ESymbolStatus;
  using CStatusData = CTextPalette::CStatusData;
  using CSessionTextSequencer = NSKernel::CSessionTextSequencer;

  using CQCharBuffer = std::vector<QChar>;

  using CQTextDocUptr = std::unique_ptr<QTextDocument>;
  using CCacher = NSKernel::CTextModeCacher<CQTextDocUptr>;

public:
  explicit CTextPrinterImpl(QPlainTextEdit* TextEdit);
  ~CTextPrinterImpl();

  CTextDataObserver* textDataInput();

private:
  void handleTextData(const CTextData& data);
  CQTextDocUptr makeText(const CTextData& data);

  template<class TNode>
  CStatusData getStatus(const TNode& Node) const;
  template<class TConstIterator>
  CStatusData extractToBuffer(CStatusData Current,
                              const TConstIterator sentinel,
                              TConstIterator* pIter);
  template<class TText>
  CQTextDocUptr makeFormattedText(const TText& TextView);

  CQTextDocUptr makeFormattedTextS(CSessionTextSequencer Sequencer);
  CStatusData extractToBufferS(CStatusData StatusData,
                               CSessionTextSequencer* pSequencer);

  void setFormat(CStatusData Status, QTextCursor* pTextCursor) const;
  void insertTextFromBuffer(QTextCursor* pTextCursor) const;

  void clear();
  void setDefaultBackgroundColor();

  static QColor shade(QColor Color, unsigned char Depth);
  static CQTextDocUptr getDefaultDocUptr();

  static constexpr const size_t kDefaultBufferSize = 128;
  static constexpr const int kDefaultFontSize = 14;

  QPlainTextEdit* TextEdit_;
  CQTextDocUptr Text_;
  CTextDataInput TextDataInput_;
  CQCharBuffer buffer_ = CQCharBuffer(kDefaultBufferSize);
  CTextPalette Palette_;
  CTime TimeLimit_ = CTime::MilliSeconds(50);
  CCacher Cacher_;
};

} // namespace NSTextPrinterDetail

using CTextPrinter =
    NSLibrary::CViewWrapper<NSTextPrinterDetail::CTextPrinterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H
