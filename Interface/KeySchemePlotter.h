#ifndef NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H
#define NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H

#include "Kernel/KeyScheme.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

#include <QColor>

#include <array>

class QwtPlot;

namespace NSApplication {
namespace NSInterface {

struct CKeySchemePalette {
  enum EPlotItem : unsigned char { KeyArea, KeyBorder, Text, End };

  std::array<QColor, EPlotItem::End> Colors{{{255, 229, 204} /*KeyArea*/,
                                             {0, 0, 0} /*KeyBorder*/,
                                             {0, 0, 0} /*Text*/}};
  qreal border_width = 2;
};

namespace NSKeySchemePlotterDetail {

class CKeySchemePlotterImpl {
  using CKeyScheme = NSKernel::CKeyScheme;
  using CKeySegment = CKeyScheme::CKeySegment;

  using CKeySchemeObserver = NSLibrary::CObserver<CKeyScheme>;
  using CKeySchemeInput = NSLibrary::CHotInput<CKeyScheme>;

  using CKeySegmentContainer = CKeyScheme::CKeySegmentContainer;

public:
  CKeySchemePlotterImpl(QwtPlot* Plot);

  CKeySchemeObserver* keySchemeInput();

private:
  void handleKeyScheme(const CKeyScheme& KeyScheme);

  void adjustPlot();
  void setAxis();
  void setGrid();

  void clear();

  void drawKeysAt(int Position, const CKeySegmentContainer& Data);
  void drawKeyAreas(int Position, const CKeySegment& Key);
  void drawKeyContour(int Position, const CKeySegment& Key);
  void drawKeyText(int Position, const CKeySegment& Key);

  void addArea(int Position, double Begin, double End,
               unsigned char multiplicity);
  void addContour(int Position, double Begin, double End);
  static QColor shade(QColor Color, unsigned char Depth);

  QwtPlot* Plot_;
  CKeySchemePalette KeySchemePalette_;
  CKeySchemeInput KeySchemeInput_;
};

} // namespace NSKeySchemePlotterDetail

using CKeySchemePlotter =
    NSLibrary::CViewWrapper<NSKeySchemePlotterDetail::CKeySchemePlotterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H
