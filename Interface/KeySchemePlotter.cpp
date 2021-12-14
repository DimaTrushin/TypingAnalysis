#include "KeySchemePlotter.h"

#include "qwt_plot.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_magnifier.h"
#include "qwt_plot_marker.h"
#include "qwt_plot_panner.h"
#include "qwt_plot_shapeitem.h"
#include "qwt_scale_draw.h"
#include "qwt_symbol.h"
#include "qwt_text.h"

#include <QPainterPath>
#include <QPen>

#include <cassert>

namespace NSApplication {
namespace NSInterface {

namespace NSKeySchemePlotterDetail {

namespace {

class LabelDefaultScaleDraw : public QwtScaleDraw {
  QwtText label(double) const override {
    return QString("");
  }
};

class LabelScaleDraw : public QwtScaleDraw {
  using CStringContainer = std::vector<QString>;

public:
  LabelScaleDraw(CStringContainer&& list) : Text_(std::move(list)) {
  }
  QwtText label(double value) const override {
    if (value < 0 || size_t(value) >= Text_.size())
      return QString("");
    return Text_[size_t(value)];
  }

private:
  CStringContainer Text_;
};

} // namespace

CKeySchemePlotterImpl::CKeySchemePlotterImpl(QwtPlot* Plot)
    : Plot_(Plot), KeySchemeInput_([this](const CKeyScheme& KeyScheme) {
        handleKeyScheme(KeyScheme);
      }),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }) {
  assert(Plot_);
  adjustPlot();
  setAxis();
  setGrid();
  setNavigation();
}

CKeySchemePlotterImpl::CKeySchemeObserver*
CKeySchemePlotterImpl::keySchemeInput() {
  return &KeySchemeInput_;
}

CKeySchemePlotterImpl::CLocalizerObserver*
CKeySchemePlotterImpl::localizerInput() {
  return &LocalizerInput_;
}

void CKeySchemePlotterImpl::handleKeyScheme(const CKeyScheme& KeyScheme) {
  clear();
  setYAxisNames(KeyScheme);
  int Position = 0;
  for (const auto& FingerData : KeyScheme) {
    drawKeysAt(Position, FingerData.second);
    ++Position;
  }
  Plot_->replot();
}

void CKeySchemePlotterImpl::adjustPlot() {
  Plot_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  Plot_->setTitle(title());
  Plot_->setMinimumHeight(300);
}

void CKeySchemePlotterImpl::setAxis() {
  Plot_->setAxisScale(QwtAxis::XBottom, kDefaultLeftBorder,
                      kDefaultRightBorder);
  Plot_->setAxisTitle(QwtAxis::XBottom, timeAxisTitle());
  Plot_->setAxisScaleDraw(QwtAxis::YLeft, new LabelDefaultScaleDraw());
  Plot_->setAxisScale(QwtAxis::YLeft, -0.5, 9.5, 1.0);
  Plot_->setAxisMaxMajor(QwtAxis::YLeft, 10);
  Plot_->setAxisMaxMinor(QwtAxis::YLeft, 3);
  Plot_->setAxisTitle(QwtAxis::YLeft, fingerAxisTitle());
}

void CKeySchemePlotterImpl::setGrid() {
  std::unique_ptr<QwtPlotGrid> grid = std::make_unique<QwtPlotGrid>();
  grid->enableX(false);
  grid->enableYMin(true);
  grid->setMajorPen(Qt::gray, 0, Qt::NoPen);
  grid->setMinorPen(Qt::gray, 0, Qt::SolidLine);
  grid.release()->attach(Plot_);
}

void CKeySchemePlotterImpl::setNavigation() {
  QwtPlotMagnifier* Mag = new QwtPlotMagnifier(Plot_->canvas());
  Mag->setAxisEnabled(QwtAxis::YLeft, false);

  QwtPlotPanner* panner = new QwtPlotPanner(Plot_->canvas());
  panner->setAxisEnabled(QwtAxis::YLeft, false);
}

void CKeySchemePlotterImpl::clear() {
  Plot_->detachItems();
  setGrid();
  Plot_->setAxisScale(QwtAxis::XBottom, kDefaultLeftBorder,
                      kDefaultRightBorder);
}

void CKeySchemePlotterImpl::setYAxisNames(const CKeyScheme& KeyScheme) {
  Plot_->setAxisScaleDraw(QwtAxis::YLeft,
                          new LabelScaleDraw(getFingerNames(KeyScheme)));
  Plot_->setAxisScale(QwtAxis::YLeft, -0.5,
                      static_cast<double>(KeyScheme.size()) - 0.5, 1.0);
  Plot_->setAxisMaxMajor(QwtAxis::YLeft, static_cast<int>(KeyScheme.size()));
  Plot_->setAxisMaxMinor(QwtAxis::YLeft, 3);
}

void CKeySchemePlotterImpl::drawKeysAt(int Position,
                                       const CKeySegmentContainer& Data) {
  for (const auto& Key : Data) {
    drawKeyAreas(Position, Key);
    drawKeyContour(Position, Key);
    drawKeyText(Position, Key);
  }
}

void CKeySchemePlotterImpl::drawKeyAreas(int Position, const CKeySegment& Key) {
  CTime Begin = Key.getPressingTime();
  for (const auto& Segment : Key) {
    CTime End = Segment.EndTime;
    addArea(Position, Begin.toMilliSecondsF(), End.toMilliSecondsF(),
            Segment.Multiplicity);
    Begin = End;
  }
}

void CKeySchemePlotterImpl::drawKeyContour(int Position,
                                           const CKeySegment& Key) {
  addContour(Position, Key.getPressingTime().toMilliSecondsF(),
             Key.getReleasingTime().toMilliSecondsF());
}

void CKeySchemePlotterImpl::drawKeyText(int Position, const CKeySegment& Key) {
  std::unique_ptr<QwtPlotMarker> Marker = std::make_unique<QwtPlotMarker>();
  QwtText text(Key.getText());
  //  text.setFont(QFont("Helvetica", 10, QFont::Bold));
  text.setColor(KeySchemePalette_.Colors[CKeySchemePalette::Text]);
  double center =
      (Key.getPressingTime() + Key.getReleasingTime()).toMilliSecondsF() / 2;
  Marker->setValue(center, Position);
  Marker->setLabelAlignment(Qt::AlignCenter);
  Marker->setLabel(text);
  Marker.release()->attach(Plot_);
}

void CKeySchemePlotterImpl::addArea(int Position, double Begin, double End,
                                    unsigned char multiplicity) {
  QwtPlotShapeItem* item = new QwtPlotShapeItem();
  QRectF rect;
  rect.setCoords(Begin, Position - 0.5 + 0.05, End, Position + 0.5 - 0.05);
  QPainterPath path;
  path.addRect(rect);
  item->setShape(path);
  item->setBrush(shade(KeySchemePalette_.Colors[CKeySchemePalette::KeyArea],
                       multiplicity));
  QPen pen = QPen(
      shade(KeySchemePalette_.Colors[CKeySchemePalette::KeyArea], multiplicity),
      0);
  item->setPen(pen);
  item->attach(Plot_);
}

void CKeySchemePlotterImpl::addContour(int Position, double Begin, double End) {
  QwtPlotShapeItem* item = new QwtPlotShapeItem();
  QRectF rect;
  rect.setCoords(Begin, Position - 0.5 + 0.05, End, Position + 0.5 - 0.05);
  QPainterPath path;
  path.addRect(rect);
  item->setShape(path);
  QPen pen = QPen(KeySchemePalette_.Colors[CKeySchemePalette::KeyBorder],
                  KeySchemePalette_.border_width);
  item->setPen(pen);
  item->attach(Plot_);
}

QColor CKeySchemePlotterImpl::shade(QColor Color, unsigned char Depth) {
  int h, s, l;
  Depth = std::min<unsigned char>(Depth, 10);
  Color.getHsv(&h, &s, &l);
  l = (l > 20 * Depth ? l - 20 * Depth : 0);
  return QColor::fromHsv(h, s, l);
}

QString CKeySchemePlotterImpl::getFingerName(const CFinger& Finger) const {
  // TO DO
  // preliminary implementation
  if (!LocalizerInput_.hasValue())
    return "";
  switch (Finger.id()) {
  case EFingerEnum::Left | EFingerEnum::Thumb:
    return LocalizerInput_.data()->get().leftThumb();
  case EFingerEnum::Left | EFingerEnum::Index:
    return LocalizerInput_.data()->get().leftIndex();
  case EFingerEnum::Left | EFingerEnum::Middle:
    return LocalizerInput_.data()->get().leftMiddle();
  case EFingerEnum::Left | EFingerEnum::Ring:
    return LocalizerInput_.data()->get().leftRing();
  case EFingerEnum::Left | EFingerEnum::Pinky:
    return LocalizerInput_.data()->get().leftPinky();
  case EFingerEnum::Right | EFingerEnum::Thumb:
    return LocalizerInput_.data()->get().rightThumb();
  case EFingerEnum::Right | EFingerEnum::Index:
    return LocalizerInput_.data()->get().rightIndex();
  case EFingerEnum::Right | EFingerEnum::Middle:
    return LocalizerInput_.data()->get().rightMiddle();
  case EFingerEnum::Right | EFingerEnum::Ring:
    return LocalizerInput_.data()->get().rightRing();
  case EFingerEnum::Right | EFingerEnum::Pinky:
    return LocalizerInput_.data()->get().rightPinky();
  case EFingerEnum::Undefined:
    return LocalizerInput_.data()->get().undefined();
  default:
    return "";
  }
}

std::vector<QString>
CKeySchemePlotterImpl::getFingerNames(const CKeyScheme& KeyScheme) const {
  std::vector<QString> Names(KeyScheme.size());
  auto iter = Names.begin();
  for (const auto& KeyData : KeyScheme) {
    *iter = getFingerName(KeyData.first);
    ++iter;
  }
  return Names;
}

void CKeySchemePlotterImpl::setLocale(const CLocalizer& Localizer) {
  Plot_->setTitle(Localizer.title());
  Plot_->setAxisTitle(QwtAxis::XBottom, Localizer.timeAxisTitle());
  Plot_->setAxisTitle(QwtAxis::YLeft, Localizer.fingerAxisTitle());
  if (KeySchemeInput_.hasValue())
    setYAxisNames(KeySchemeInput_.data()->get());
}

QString CKeySchemePlotterImpl::title() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().title();
}

QString CKeySchemePlotterImpl::timeAxisTitle() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().timeAxisTitle();
}

QString CKeySchemePlotterImpl::fingerAxisTitle() const {
  if (!LocalizerInput_.hasValue())
    return "";
  return LocalizerInput_.data()->get().fingerAxisTitle();
}

} // namespace NSKeySchemePlotterDetail
} // namespace NSInterface
} // namespace NSApplication
