#ifndef NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H
#define NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H

#include "Kernel/KeyScheme.h"
#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/Localizer.h"

#include <QColor>

#include <array>

class QwtPlot;

QT_BEGIN_NAMESPACE
class QFrame;
class QVBoxLayout;
// class QSlider;
// class QGridLayout;
QT_END_NAMESPACE

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
  using CFinger = NSKernel::CFinger;
  using EFingerEnum = CFinger::EFingerEnum;

  using CKeySchemeObserver = NSLibrary::CObserver<CKeyScheme>;
  using CKeySchemeInput = NSLibrary::CHotInput<CKeyScheme>;

  using CLocalizer = NSLocal::CKeySchemePlotterLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

  using CKeySegmentContainer = CKeyScheme::CKeySegmentContainer;

public:
  CKeySchemePlotterImpl(QFrame* Frame);

  CKeySchemeObserver* keySchemeInput();
  CLocalizerObserver* localizerInput();

private:
  void handleKeyScheme(const CKeyScheme& KeyScheme);

  void adjustPlot(QVBoxLayout* Layout);
  void setAxis();
  void setGrid();
  void setNavigation();

  void clear();
  void setYAxisNames(const CKeyScheme& KeyScheme);
  void drawKeysAt(int Position, const CKeySegmentContainer& Data);
  void drawKeyAreas(int Position, const CKeySegment& Key);
  void drawKeyContour(int Position, const CKeySegment& Key);
  void drawKeyText(int Position, const CKeySegment& Key);

  void addArea(int Position, double Begin, double End,
               unsigned char multiplicity);
  void addContour(int Position, double Begin, double End);
  static QColor shade(QColor Color, unsigned char Depth);

  QString getFingerName(const CFinger& Finger) const;
  std::vector<QString> getFingerNames(const CKeyScheme& KeyScheme) const;

  void setLocale(const CLocalizer& Localizer);
  QString title() const;
  QString timeAxisTitle() const;
  QString fingerAxisTitle() const;

  static constexpr const double kDefaultLeftBorder = 0.0;
  static constexpr const double kDefaultRightBorder = 3000.0;

  QFrame* ParentFrame_;
  QwtPlot* Plot_;
  CKeySchemePalette KeySchemePalette_;
  CKeySchemeInput KeySchemeInput_;
  CLocalizerInput LocalizerInput_;
};

} // namespace NSKeySchemePlotterDetail

using CKeySchemePlotter =
    NSLibrary::CViewWrapper<NSKeySchemePlotterDetail::CKeySchemePlotterImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CKEYSCHEMEPLOTTER_H
