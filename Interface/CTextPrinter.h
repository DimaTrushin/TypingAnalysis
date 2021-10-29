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

  using CSession = NSKernel::CSession;
  using CTextDataTree = NSKernel::CTextDataTree;
  using ETextMode = NSKernel::ETextMode;

public:
  CTextPrinterImpl(QTextEdit* TextEdit);

  CTextDataObserver* textDataInput();

private:
  void handleTextData(const CTextData& data);
  void printSession(const CSession& Session);
  void printFullText(const CTextDataTree& TextTree);
  void printPrintedText(const CTextDataTree& TextTree);

  QTextEdit* TextEdit_;
  CTextDataInput TextDataInput_;
};

} // namespace NSTextPrinterDetail

using CTextPrinter =
    NSLibrary::CViewWrapper<NSTextPrinterDetail::CTextPrinterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTPRINTER_H
