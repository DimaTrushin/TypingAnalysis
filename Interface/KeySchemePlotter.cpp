#include "KeySchemePlotter.h"

#include "qwt_plot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_marker.h"
#include "qwt_plot_shapeitem.h"
#include "qwt_scale_draw.h"
#include "qwt_symbol.h"
#include "qwt_text.h"

#include <QDebug>
#include <QPainterPath>
#include <QPen>

#include <cassert>

namespace NSApplication {
namespace NSInterface {

namespace NSKeySchemePlotterDetail {

namespace {

class LabelScaleDraw : public QwtScaleDraw {
  QwtText label(double value) const override {
    // TO DO
    // Need to reimplement this
    switch (int(value)) {
    case 0:
      return QString("Thumb");
    case 1:
      return QString("Left Pinky");
    case 2:
      return QString("Left Ring");
    case 3:
      return QString("Left Middle");
    case 4:
      return QString("Left Index");
    case 5:
      return QString("Right Index");
    case 6:
      return QString("Right Middle");
    case 7:
      return QString("Right Ring");
    case 8:
      return QString("Right Pinky");
    case 9:
      return QString("Unassigned");
    default:
      break;
    }
    return QwtScaleDraw::label(value);
  }
};
} // namespace

CKeySchemePlotterImpl::CKeySchemePlotterImpl(QwtPlot* Plot)
    : Plot_(Plot), KeySchemeInput_([this](const CKeyScheme& KeyScheme) {
        handleKeyScheme(KeyScheme);
      }) {
  assert(Plot_);
  adjustPlot();
  setAxis();
  setGrid();
}

CKeySchemePlotterImpl::CKeySchemeObserver*
CKeySchemePlotterImpl::keySchemeInput() {
  return &KeySchemeInput_;
}

void CKeySchemePlotterImpl::handleKeyScheme(const CKeyScheme& KeyScheme) {
  clear();
  // TO DO
  // reset axist according to KeyScheme
  int Position = 0;
  for (const auto& FingerData : KeyScheme) {
    drawKeysAt(Position, FingerData.second);
    ++Position;
  }
  Plot_->replot();
}

void CKeySchemePlotterImpl::adjustPlot() {
  Plot_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  Plot_->setTitle("Key Scheme");
  Plot_->setMinimumHeight(300);
}

void CKeySchemePlotterImpl::setAxis() {
  Plot_->setAxisTitle(QwtAxis::XBottom, "Time, ms");
  Plot_->setAxisScale(QwtAxis::XBottom, 0.0, 3000);
  Plot_->setAxisScaleDraw(QwtAxis::YLeft, new LabelScaleDraw());
  Plot_->setAxisScale(QwtAxis::YLeft, -0.5, 9.5, 1.0);
  Plot_->setAxisMaxMajor(QwtAxis::YLeft, 10);
  Plot_->setAxisMaxMinor(QwtAxis::YLeft, 3);
  Plot_->setAxisTitle(QwtAxis::YLeft, "Fingers");
}

void CKeySchemePlotterImpl::setGrid() {
  std::unique_ptr<QwtPlotGrid> grid = std::make_unique<QwtPlotGrid>();
  grid->enableX(false);
  grid->enableYMin(true);
  grid->setMajorPen(Qt::gray, 0, Qt::NoPen);
  grid->setMinorPen(Qt::gray, 0, Qt::SolidLine);
  grid.release()->attach(Plot_);
}

void CKeySchemePlotterImpl::clear() {
  Plot_->detachItems();
  setGrid();
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
  // TO DO
  // Preliminary implementation
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
  l = (l > 15 * Depth ? l - 15 * Depth : 0);
  return QColor::fromHsv(h, s, l);
}

} // namespace NSKeySchemePlotterDetail
} // namespace NSInterface
} // namespace NSApplication
