#ifndef NSAPPLICATION_NSLOCAL_CLOCALIZER_H
#define NSAPPLICATION_NSLOCAL_CLOCALIZER_H

#include <QString>

namespace NSApplication {
namespace NSLocal {

namespace NSLocalizerDetail {
template<class T>
struct Data {};
} // namespace NSLocalizerDetail

class CSeanceViewLocalizer {
public:
  template<class TSeanceViewLocale>
  static CSeanceViewLocalizer make() {
    return CSeanceViewLocalizer(NSLocalizerDetail::Data<TSeanceViewLocale>());
  }

  const QString& description() const {
    return Description_;
  }
  const QString& size() const {
    return Size_;
  }
  const QString& currentSeance() const {
    return CurrentSeance_;
  }

private:
  template<class TSeanceViewLocale>
  CSeanceViewLocalizer(NSLocalizerDetail::Data<TSeanceViewLocale>)
      : Description_(TSeanceViewLocale::Description),
        Size_(TSeanceViewLocale::Size),
        CurrentSeance_(TSeanceViewLocale::CurrentSeance) {
  }

  QString Description_;
  QString Size_;
  QString CurrentSeance_;
};

class CStatisticsViewLocalizer {
public:
  template<class TStatisticsViewLocale>
  static CStatisticsViewLocalizer make() {
    return CStatisticsViewLocalizer(
        NSLocalizerDetail::Data<TStatisticsViewLocale>());
  }

  const QString& data() const {
    return Data_;
  }
  const QString& value() const {
    return Value_;
  }

private:
  template<class TStatisticsViewLocale>
  CStatisticsViewLocalizer(NSLocalizerDetail::Data<TStatisticsViewLocale>)
      : Data_(TStatisticsViewLocale::Data),
        Value_(TStatisticsViewLocale::Value) {
  }
  QString Data_;
  QString Value_;
};

class CStatisticsLocalizer {
public:
  template<class TStatisticsLocale>
  static CStatisticsLocalizer make() {
    return CStatisticsLocalizer(NSLocalizerDetail::Data<TStatisticsLocale>());
  }
  const QString& fullTextLength() const {
    return FullTextLength_;
  }
  const QString& printedTextLength() const {
    return PrintedTextLength_;
  }
  const QString& deletedSymbols() const {
    return DeletedSymbols_;
  }
  const QString& mistakePlaces() const {
    return MistakePlaces_;
  }
  const QString& mistakes() const {
    return Mistakes_;
  }
  const QString& mistakesPercent() const {
    return MistakesPercent_;
  }
  const QString& printedTextDuration() const {
    return PrintedTextDuration_;
  }
  const QString& printedTextSpeed() const {
    return PrintedTextSpeed_;
  }
  const QString& maxLikelihoodSpeed() const {
    return MaxLikelihoodSpeed_;
  }
  const QString& score() const {
    return Score_;
  }

  const QString& fullTextLengthHint() const {
    return FullTextLengthHint_;
  }
  const QString& printedTextLengthHint() const {
    return PrintedTextLengthHint_;
  }
  const QString& deletedSymbolsHint() const {
    return DeletedSymbolsHint_;
  }
  const QString& mistakePlacesHint() const {
    return MistakePlacesHint_;
  }
  const QString& mistakesHint() const {
    return MistakesHint_;
  }
  const QString& mistakesPercentHint() const {
    return MistakesPercentHint_;
  }
  const QString& printedTextDurationHint() const {
    return PrintedTextDurationHint_;
  }
  const QString& printedTextSpeedHint() const {
    return PrintedTextSpeedHint_;
  }
  const QString& maxLikelihoodSpeedHint() const {
    return MaxLikelihoodSpeedHint_;
  }
  const QString& scoreHint() const {
    return ScoreHint_;
  }

private:
  template<class TStatisticsLocale>
  CStatisticsLocalizer(NSLocalizerDetail::Data<TStatisticsLocale>)
      : FullTextLength_(TStatisticsLocale::FullTextLength),
        PrintedTextLength_(TStatisticsLocale::PrintedTextLength),
        DeletedSymbols_(TStatisticsLocale::DeletedSymbols),
        MistakePlaces_(TStatisticsLocale::MistakePlaces),
        Mistakes_(TStatisticsLocale::Mistakes),
        MistakesPercent_(TStatisticsLocale::MistakesPercent),
        PrintedTextDuration_(TStatisticsLocale::PrintedTextDuration),
        PrintedTextSpeed_(TStatisticsLocale::PrintedTextSpeed),
        MaxLikelihoodSpeed_(TStatisticsLocale::MaxLikelihoodSpeed),
        Score_(TStatisticsLocale::Score),

        FullTextLengthHint_(TStatisticsLocale::FullTextLengthHint),
        PrintedTextLengthHint_(TStatisticsLocale::PrintedTextLengthHint),
        DeletedSymbolsHint_(TStatisticsLocale::DeletedSymbolsHint),
        MistakePlacesHint_(TStatisticsLocale::MistakePlacesHint),
        MistakesHint_(TStatisticsLocale::MistakesHint),
        MistakesPercentHint_(TStatisticsLocale::MistakesPercentHint),
        PrintedTextDurationHint_(TStatisticsLocale::PrintedTextDurationHint),
        PrintedTextSpeedHint_(TStatisticsLocale::PrintedTextSpeedHint),
        MaxLikelihoodSpeedHint_(TStatisticsLocale::MaxLikelihoodSpeedHint),
        ScoreHint_(TStatisticsLocale::ScoreHint) {
  }

  QString FullTextLength_;
  QString PrintedTextLength_;
  QString DeletedSymbols_;
  QString MistakePlaces_;
  QString Mistakes_;
  QString MistakesPercent_;
  QString PrintedTextDuration_;
  QString PrintedTextSpeed_;
  QString MaxLikelihoodSpeed_;
  QString Score_;

  QString FullTextLengthHint_;
  QString PrintedTextLengthHint_;
  QString DeletedSymbolsHint_;
  QString MistakePlacesHint_;
  QString MistakesHint_;
  QString MistakesPercentHint_;
  QString PrintedTextDurationHint_;
  QString PrintedTextSpeedHint_;
  QString MaxLikelihoodSpeedHint_;
  QString ScoreHint_;
};

class CTextModeViewLocalizer {
public:
  template<class TTextModeViewLocale>
  static CTextModeViewLocalizer make() {
    return CTextModeViewLocalizer(
        NSLocalizerDetail::Data<TTextModeViewLocale>());
  }

  const QString& textMode() const {
    return TextMode_;
  }
  const QString& raw() const {
    return Raw_;
  }
  const QString& full() const {
    return Full_;
  }
  const QString& printed() const {
    return Printed_;
  }
  const QString& non() const {
    return Non_;
  }
  const QString& all() const {
    return All_;
  }
  const QString& essential() const {
    return Essential_;
  }
  const QString& shift() const {
    return Shift_;
  }
  const QString& ctrl() const {
    return Ctrl_;
  }
  const QString& alt() const {
    return Alt_;
  }
  const QString& modifiers() const {
    return Modifiers_;
  }
  const QString& rawHint() const {
    return RawHint_;
  }
  const QString& fullHint() const {
    return FullHint_;
  }
  const QString& printedHint() const {
    return PrintedHint_;
  }
  const QString& nonHint() const {
    return NonHint_;
  }
  const QString& allHint() const {
    return AllHint_;
  }
  const QString& essentialHint() const {
    return EssentialHint_;
  }

private:
  template<class TTextModeViewLocale>
  CTextModeViewLocalizer(NSLocalizerDetail::Data<TTextModeViewLocale>)
      : TextMode_(TTextModeViewLocale::TextMode),
        Raw_(TTextModeViewLocale::Raw), Full_(TTextModeViewLocale::Full),
        Printed_(TTextModeViewLocale::Printed), Non_(TTextModeViewLocale::Non),
        All_(TTextModeViewLocale::All),
        Essential_(TTextModeViewLocale::Essential),
        Shift_(TTextModeViewLocale::Shift), Ctrl_(TTextModeViewLocale::Ctrl),
        Alt_(TTextModeViewLocale::Alt),
        Modifiers_(TTextModeViewLocale::Modifiers),

        RawHint_(TTextModeViewLocale::RawHint),
        FullHint_(TTextModeViewLocale::FullHint),
        PrintedHint_(TTextModeViewLocale::PrintedHint),
        NonHint_(TTextModeViewLocale::NonHint),
        AllHint_(TTextModeViewLocale::AllHint),
        EssentialHint_(TTextModeViewLocale::EssentialHint) {
  }

  QString TextMode_;
  QString Raw_;
  QString Full_;
  QString Printed_;
  QString Non_;
  QString All_;
  QString Essential_;
  QString Shift_;
  QString Ctrl_;
  QString Alt_;
  QString Modifiers_;

  QString RawHint_;
  QString FullHint_;
  QString PrintedHint_;
  QString NonHint_;
  QString AllHint_;
  QString EssentialHint_;
};

class CSpeedPlotterLocalizer {
public:
  template<class TSpeedPlotterLocale>
  static CSpeedPlotterLocalizer make() {
    return CSpeedPlotterLocalizer(
        NSLocalizerDetail::Data<TSpeedPlotterLocale>());
  }

  const QString& plotterTitle() const {
    return PlotterTitle_;
  }
  const QString& horizontalAxisTitle() const {
    return HorizontalAxisTitle_;
  }
  const QString& density1Name() const {
    return Density1Name_;
  }
  const QString& derivative1Name() const {
    return Derivative1Name_;
  }
  const QString& density2Name() const {
    return Density2Name_;
  }
  const QString& derivative2Name() const {
    return Derivative2Name_;
  }
  const QString& density3Name() const {
    return Density3Name_;
  }
  const QString& derivative3Name() const {
    return Derivative3Name_;
  }
  const QString& legendHint() const {
    return LegendHint_;
  }

private:
  template<class TSpeedPlotterLocale>
  CSpeedPlotterLocalizer(NSLocalizerDetail::Data<TSpeedPlotterLocale>)
      : PlotterTitle_(TSpeedPlotterLocale::PlotterTitle),
        HorizontalAxisTitle_(TSpeedPlotterLocale::HorizontalAxisTitle),
        Density1Name_(TSpeedPlotterLocale::Density1Name),
        Derivative1Name_(TSpeedPlotterLocale::Derivative1Name),
        Density2Name_(TSpeedPlotterLocale::Density2Name),
        Derivative2Name_(TSpeedPlotterLocale::Derivative2Name),
        Density3Name_(TSpeedPlotterLocale::Density3Name),
        Derivative3Name_(TSpeedPlotterLocale::Derivative3Name),
        LegendHint_(TSpeedPlotterLocale::LegendHint) {
  }

  QString PlotterTitle_;
  QString HorizontalAxisTitle_;
  QString Density1Name_;
  QString Derivative1Name_;
  QString Density2Name_;
  QString Derivative2Name_;
  QString Density3Name_;
  QString Derivative3Name_;
  QString LegendHint_;
};

class CKeySchemePlotterLocalizer {
public:
  template<class TKeySchemePlotterLocale>
  static CKeySchemePlotterLocalizer make() {
    return CKeySchemePlotterLocalizer(
        NSLocalizerDetail::Data<TKeySchemePlotterLocale>());
  }
  const QString& title() const {
    return Title_;
  }
  const QString& fingerAxisTitle() const {
    return FingerAxisTitle_;
  }
  const QString& timeAxisTitle() const {
    return TimeAxisTitle_;
  }
  const QString& leftThumb() const {
    return LeftThumb_;
  }
  const QString& leftIndex() const {
    return LeftIndex_;
  }
  const QString& leftMiddle() const {
    return LeftMiddle_;
  }
  const QString& leftRing() const {
    return LeftRing_;
  }
  const QString& leftPinky() const {
    return LeftPinky_;
  }
  const QString& rightThumb() const {
    return RightThumb_;
  }
  const QString& rightIndex() const {
    return RightIndex_;
  }
  const QString& rightMiddle() const {
    return RightMiddle_;
  }
  const QString& rightRing() const {
    return RightRing_;
  }
  const QString& rightPinky() const {
    return RightPinky_;
  }
  const QString& undefined() const {
    return Undefined_;
  }

private:
  template<class TKeySchemePlotterLocale>
  CKeySchemePlotterLocalizer(NSLocalizerDetail::Data<TKeySchemePlotterLocale>)
      : Title_(TKeySchemePlotterLocale::Title),
        FingerAxisTitle_(TKeySchemePlotterLocale::FingerAxisTitle),
        TimeAxisTitle_(TKeySchemePlotterLocale::TimeAxisTitle),
        LeftThumb_(TKeySchemePlotterLocale::LeftThumb),
        LeftIndex_(TKeySchemePlotterLocale::LeftIndex),
        LeftMiddle_(TKeySchemePlotterLocale::LeftMiddle),
        LeftRing_(TKeySchemePlotterLocale::LeftRing),
        LeftPinky_(TKeySchemePlotterLocale::LeftPinky),
        RightThumb_(TKeySchemePlotterLocale::RightThumb),
        RightIndex_(TKeySchemePlotterLocale::RightIndex),
        RightMiddle_(TKeySchemePlotterLocale::RightMiddle),
        RightRing_(TKeySchemePlotterLocale::RightRing),
        RightPinky_(TKeySchemePlotterLocale::RightPinky),
        Undefined_(TKeySchemePlotterLocale::Undefined) {
  }

  QString Title_;
  QString FingerAxisTitle_;
  QString TimeAxisTitle_;
  QString LeftThumb_;
  QString LeftIndex_;
  QString LeftMiddle_;
  QString LeftRing_;
  QString LeftPinky_;
  QString RightThumb_;
  QString RightIndex_;
  QString RightMiddle_;
  QString RightRing_;
  QString RightPinky_;
  QString Undefined_;
};

class CFileMenuLocalizer {
public:
  template<class TFileMenuLocale>
  static CFileMenuLocalizer make() {
    return CFileMenuLocalizer(NSLocalizerDetail::Data<TFileMenuLocale>());
  }

  const QString& menu() const {
    return Menu_;
  }
  const QString& save() const {
    return Save_;
  }
  const QString& load() const {
    return Load_;
  }

private:
  template<class TFileMenuLocale>
  CFileMenuLocalizer(NSLocalizerDetail::Data<TFileMenuLocale>)
      : Menu_(TFileMenuLocale::Menu), Save_(TFileMenuLocale::Save),
        Load_(TFileMenuLocale::Load) {
  }

  QString Menu_;
  QString Save_;
  QString Load_;
};

class CLocalizer {
public:
  template<class TLocale>
  static CLocalizer make() {
    return CLocalizer(NSLocalizerDetail::Data<TLocale>());
  }

  const CSeanceViewLocalizer& getSeanceViewLocalizer() const {
    return SeanceViewLocalizer_;
  }

  const CStatisticsViewLocalizer& getStatisticsViewLocalizer() const {
    return StatisticsViewLocalizer_;
  }

  const CStatisticsLocalizer& getStatisticsLoalizer() const {
    return StatisticsLocalizer_;
  }

  const CTextModeViewLocalizer& getTextModeViewLocalizer() const {
    return TextModeViewLocalizer_;
  }

  const CSpeedPlotterLocalizer& getSpeedPlotterLocalizer() const {
    return SpeedPlotterLocalizer_;
  }

  const CKeySchemePlotterLocalizer& getKeySchemePlotterLocalizer() const {
    return KeySchemePlotterLocalizer_;
  }

  const CFileMenuLocalizer& getFileMenuLocalizer() const {
    return FileMenuLocalizer_;
  }

private:
  template<class TLocale>
  CLocalizer(NSLocalizerDetail::Data<TLocale>)
      : SeanceViewLocalizer_(
            CSeanceViewLocalizer::make<typename TLocale::CSeanceView>()),
        StatisticsViewLocalizer_(CStatisticsViewLocalizer::make<
                                 typename TLocale::CStatisticsView>()),
        StatisticsLocalizer_(
            CStatisticsLocalizer::make<typename TLocale::CStatistics>()),
        TextModeViewLocalizer_(
            CTextModeViewLocalizer::make<typename TLocale::CTextModeView>()),
        SpeedPlotterLocalizer_(
            CSpeedPlotterLocalizer::make<typename TLocale::CSpeedPlotter>()),
        KeySchemePlotterLocalizer_(CKeySchemePlotterLocalizer::make<
                                   typename TLocale::CKeySchemePlotter>()),
        FileMenuLocalizer_(
            CFileMenuLocalizer::make<typename TLocale::CFileMenu>()) {
  }
  CSeanceViewLocalizer SeanceViewLocalizer_;
  CStatisticsViewLocalizer StatisticsViewLocalizer_;
  CStatisticsLocalizer StatisticsLocalizer_;
  CTextModeViewLocalizer TextModeViewLocalizer_;
  CSpeedPlotterLocalizer SpeedPlotterLocalizer_;
  CKeySchemePlotterLocalizer KeySchemePlotterLocalizer_;
  CFileMenuLocalizer FileMenuLocalizer_;
};

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CLOCALIZER_H
