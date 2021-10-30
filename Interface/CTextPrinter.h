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

  using EKeyStatus = CTextPalette::EKeyStatus;

public:
  CTextPrinterImpl(QTextEdit* TextEdit);

  CTextDataObserver* textDataInput();

private:
  void handleTextData(const CTextData& data);
  void printSession(const CSession& Session);
  void printFormattedSession(const CSession& Session);
  void printFullText(const CTextDataTree& TextTree);
  void printPrintedText(const CTextDataTree& TextTree);

  EKeyStatus getKeyStatus(const CKeyEvent& Key);
  EKeyStatus extractToBuffer(EKeyStatus Status,
                             const CConstSessionIterator sentinel,
                             CConstSessionIterator* pIter);
  void printBuffer(EKeyStatus Status);
  void printBuffer(QColor Text, QColor Back);
  void clear();
  void setDefaultBackgroundColor();

  static constexpr const size_t kDefaultBufferSize = 128;

  class CColorAnchor {
  public:
    CColorAnchor(QColor Text, QColor Back, QTextEdit* TextEdit);
    ~CColorAnchor();

  private:
    QColor OldText_;
    QColor OldBack_;
    QTextEdit* TextEdit_;
  };

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
