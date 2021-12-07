#ifndef NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H
#define NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H

#include "Library/StlExtension/MvcWrappers.h"

class QwtPlot;

namespace NSApplication {
namespace NSInterface {

namespace NSKeySchemePlotterDetail {

class CKeySchemePlotterImpl {
public:
  CKeySchemePlotterImpl(QwtPlot* Plot);

private:
  QwtPlot* Plot_;
};

} // namespace NSKeySchemePlotterDetail

using CKeySchemePlotter =
    NSLibrary::CViewWrapper<NSKeySchemePlotterDetail::CKeySchemePlotterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H
