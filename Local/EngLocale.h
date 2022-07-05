#ifndef NSAPPLICATION_NSLOCAL_CENGLOCALE_H
#define NSAPPLICATION_NSLOCAL_CENGLOCALE_H

namespace NSApplication {
namespace NSLocal {

struct CEngLocale {
  struct CSeanceView {
    static constexpr const char* Description = "Description";
    static constexpr const char* Size = "Size";
    static constexpr const char* CurrentSeance = "Current Seance";
  };

  struct CStatisticsView {
    static constexpr const char* Data = "Data";
    static constexpr const char* Value = "Value";
  };
  struct CStatistics {
    static constexpr const char* FullTextLength = "Full Text Length";
    static constexpr const char* PrintedTextLength = "Printed Text Length";
    static constexpr const char* DeletedSymbols = "Symbols Deleted";
    static constexpr const char* MistakePlaces = "Erroneous Places";
    static constexpr const char* Mistakes = "Errors";
    static constexpr const char* MistakesPercent = "Error rate";
    static constexpr const char* FullTextDuration = "Full Text Duration, sec";
    static constexpr const char* PrintedTextDuration =
        "Printed Text Duration, sec";
    static constexpr const char* FullTextSpeed = "Full Text Speed, symb/min";
    static constexpr const char* PrintedTextSpeed = "Speed (real), symb/min";
    static constexpr const char* MaxLikelihoodSpeed = "Speed (main), symb/min";
  };
  struct CTextModeView {
    static constexpr const char* TextMode = "Text Mode";
    static constexpr const char* Raw = "Raw";
    static constexpr const char* Full = "Full";
    static constexpr const char* Printed = "Printed";
    static constexpr const char* Non = "Non";
    static constexpr const char* All = "All";
    static constexpr const char* Essential = "Essential";
    static constexpr const char* Shift = "Shift";
    static constexpr const char* Ctrl = "Ctrl";
    static constexpr const char* Alt = "Alt";
    static constexpr const char* Modifiers = "Modifiers";
  };

  struct CSpeedPlotter {
    static constexpr const char* PlotterTitle = "Speed Density";
    static constexpr const char* HorizontalAxisTitle = "Speed, symb/min";
    static constexpr const char* Density1Name = "Density";
    static constexpr const char* Derivative1Name = "Derivative";
    static constexpr const char* Density2Name = "Density M-B";
    static constexpr const char* Derivative2Name = "Derivative M-B";
    static constexpr const char* Density3Name = "Density R";
    static constexpr const char* Derivative3Name = "Derivative R";
  };

  struct CKeySchemePlotter {
    static constexpr const char* Title = "Key Scheme";
    static constexpr const char* FingerAxisTitle = "Fingers";
    static constexpr const char* TimeAxisTitle = "Time, ms";
    static constexpr const char* LeftThumb = "Left Thumb";
    static constexpr const char* LeftIndex = "Left Index";
    static constexpr const char* LeftMiddle = "Left Middle";
    static constexpr const char* LeftRing = "Left Ring";
    static constexpr const char* LeftPinky = "Left Pinky";
    static constexpr const char* RightThumb = "Right Thumb";
    static constexpr const char* RightIndex = "Right Index";
    static constexpr const char* RightMiddle = "Right Middle";
    static constexpr const char* RightRing = "Right Ring";
    static constexpr const char* RightPinky = "Right Pinky";
    static constexpr const char* Undefined = "Undefined";
  };
};

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CENGLOCALE_H
