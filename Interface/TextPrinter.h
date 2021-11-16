#ifndef NSAPPLICATION_NSINTERFACE_TEXTPRINTER_H
#define NSAPPLICATION_NSINTERFACE_TEXTPRINTER_H

#include "Kernel/TextData.h"
#include "Kernel/TextDataTree.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

#include <QColor>
#include <QPalette>

#include <array>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextEdit;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

struct CTextPalette {
  enum EKeyStatus : unsigned char {
    MainText,
    AccidentallyDeleted,
    RequiredDeletion,
    Erroneous,
    Backspace,
    Control,
    EssentialControl,
    SilentDeadKey,
    Ignore,
    End,
  };

  struct CStatusData {
    EKeyStatus Status;
    unsigned char Depth;

    friend bool operator==(CStatusData lhs, CStatusData rhs);
    friend bool operator!=(CStatusData lhs, CStatusData rhs);
  };

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

  using CQCharBuffer = std::vector<QChar>;

public:
  explicit CTextPrinterImpl(QTextEdit* TextEdit);

  CTextDataObserver* textDataInput();

private:
  void handleTextData(const CTextData& data);
  void printFormattedSession(const CSession& Session);
  template<class TText>
  void printFormattedText(const TText& TextView);

  EKeyStatus getKeyRawStatus(const CKeyEvent& Key);
  CStatusData getKeyTextStatus(const CTextNode& TextNode);
  EKeyStatus extractToBufferRaw(EKeyStatus Status,
                                const CConstSessionIterator sentinel,
                                CConstSessionIterator* pIter);
  template<class CConstIterator>
  CStatusData extractToBufferText(CStatusData Status,
                                  const CConstIterator sentinel,
                                  CConstIterator* pIter);
  void setFormat(CStatusData Status, QTextEdit* pTextEdit) const;
  void insertTextFromBuffer(QTextEdit* pTextEdit) const;

  void clear();
  void setDefaultBackgroundColor();

  static QColor shade(QColor Color, unsigned char Depth);

  QTextDocument* getDefaultDocument() const;

  static constexpr const size_t kDefaultBufferSize = 128;

  QTextEdit* TextEdit_;
  CTextDataInput TextDataInput_;
  CQCharBuffer buffer_ = CQCharBuffer(kDefaultBufferSize);
  CTextPalette Palette_;
};

} // namespace NSTextPrinterDetail

using CTextPrinter =
    NSLibrary::CViewWrapper<NSTextPrinterDetail::CTextPrinterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H
