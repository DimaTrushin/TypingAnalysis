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
    static constexpr const char* PrintedTextDuration =
        "Printed Text Duration, sec";
    static constexpr const char* PrintedTextSpeed = "Speed (real), symb/min";
    static constexpr const char* MaxLikelihoodSpeed = "Speed (main), symb/min";
    static constexpr const char* Score = "Score";

    static constexpr const char* FullTextLengthHint =
        "The amount of all symbols printed including deleted ones";
    static constexpr const char* PrintedTextLengthHint =
        "The amount of printed symbols without deleted ones";
    static constexpr const char* DeletedSymbolsHint =
        "The amount of deleted symbols";
    static constexpr const char* MistakePlacesHint =
        "The amount of places where errors were made (several errors may "
        "happen in one place)";
    static constexpr const char* MistakesHint = "The amount of errors";
    static constexpr const char* MistakesPercentHint =
        "Error rate, the formula is E/L*100, where E is the error rate, L is "
        "the length of the printed text (not including deleted symbols))";
    static constexpr const char* PrintedTextDurationHint =
        "The time spent on the text, it is equal to the difference between "
        "the last and the first key pressing";
    static constexpr const char* PrintedTextSpeedHint =
        "Average speed, the formula is L/T, where L is the length of the "
        "printed text, T is the duration of the printed text";
    static constexpr const char* MaxLikelihoodSpeedHint =
        "The main speed, it is the maximum of the speed density (the "
        "first plot)";
    static constexpr const char* ScoreHint =
        "The score of the typing technique measured from 0 to 1, the closer to "
        "1 is better";
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

    static constexpr const char* RawHint = "Show all key strokes";
    static constexpr const char* FullHint =
        "Show printed text with deleted symbols";
    static constexpr const char* PrintedHint =
        "Show printed text without deleted symbols";
    static constexpr const char* NonHint = "Do not show the key";
    static constexpr const char* AllHint = "Show all strokes of the key";
    static constexpr const char* EssentialHint =
        "Show the strokes of the key that affected the text in the current "
        "mode";
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

    static constexpr const char* LegendHint =
        "Density of the speed distribution is a \"continuous\" histogram of "
        "the speed distribution.\n1) Density recovered using normal "
        "noise\n2) Derivative of the density (1), it is useful to understend "
        "anomalies of the density\n3) Density recovered using "
        "Maxwell-Boltzmann noise\n4) Derivative of the density (3)\n5) "
        "Density recovered using Rayleigh noise\n6) Derivative of the density "
        "(5)";
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

  struct CFileMenu {
    static constexpr const char* Menu = "File";
    static constexpr const char* Save = "Save";
    static constexpr const char* Load = "Load";
  };
};

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CENGLOCALE_H
