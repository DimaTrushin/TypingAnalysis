#ifndef NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H
#define NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H

#include "Kernel/TextData.h"
#include "Kernel/TextDataTree.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

#include <QColor>
#include <QPalette>

QT_BEGIN_NAMESPACE
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

public:
  explicit CTextPrinterImpl(QTextEdit* TextEdit);

  CTextDataObserver* textDataInput();

private:
  void handleTextData(const CTextData& data);
  void printFormattedSession(const CSession& Session);
  template<class CConstIterator>
  void printFormattedText(const CTextDataTree& TextTree);

  EKeyStatus getKeyRawStatus(const CKeyEvent& Key);
  EKeyStatus getKeyTextStatus(const CTextNode& TextNode);
  EKeyStatus extractToBufferRaw(EKeyStatus Status,
                                const CConstSessionIterator sentinel,
                                CConstSessionIterator* pIter);
  template<class CConstIterator>
  EKeyStatus extractToBufferText(EKeyStatus Status,
                                 const CConstIterator sentinel,
                                 CConstIterator* pIter);

  void clear();
  void setDefaultBackgroundColor();

  QString coloredTextFromBuffer(EKeyStatus Status);
  QString coloredTextFromBuffer(QColor Text, QColor Back);

  static constexpr const size_t kDefaultBufferSize = 128;

  QTextEdit* TextEdit_;
  CTextDataInput TextDataInput_;
  std::vector<QChar> buffer_ = std::vector<QChar>(kDefaultBufferSize);
  CTextPalette Palette_;
};

} // namespace NSTextPrinterDetail

using CTextPrinter =
    NSLibrary::CViewWrapper<NSTextPrinterDetail::CTextPrinterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H
