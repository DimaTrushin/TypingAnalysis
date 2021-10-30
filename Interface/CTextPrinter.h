#ifndef NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H
#define NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H

#include "Kernel/TextData.h"
#include "Kernel/TextDataTree.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSTextPrinterDetail {
class CTextPrinterImpl {
  using CTextData = NSKernel::CTextData;
  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CKeyEvent = NSKernel::CKeyEvent;
  using CSession = NSKernel::CSession;
  using CConstSessionIterator = CSession::const_iterator;
  using CTextDataTree = NSKernel::CTextDataTree;
  using ETextMode = NSKernel::ETextMode;

  enum class EKeyStatus { End, Text, Special, Ignore };

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
  void printBufferAsText();
  void printBufferAsSpecial();
  void clear();

  static constexpr const size_t kDefaultBufferSize = 128;

  QTextEdit* TextEdit_;
  CTextDataInput TextDataInput_;
  std::vector<QChar> buffer_ = std::vector<QChar>(kDefaultBufferSize);
};

} // namespace NSTextPrinterDetail

using CTextPrinter =
    NSLibrary::CViewWrapper<NSTextPrinterDetail::CTextPrinterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H
