#ifndef NSAPPLICATION_NSLOCAL_CRUSLOCALE_H
#define NSAPPLICATION_NSLOCAL_CRUSLOCALE_H

namespace NSApplication {
namespace NSLocal {

struct CRusLocale {
  struct CSeanceView {
    static constexpr const char* Description = "Описание";
    static constexpr const char* Size = "Размер";
    static constexpr const char* CurrentSeance = "Текущий сеанс";
  };

  struct CStatisticsView {
    static constexpr const char* Data = "Данные";
    static constexpr const char* Value = "Значение";
  };
  struct CStatistics {
    static constexpr const char* FullTextLength = "Длина полного текста";
    static constexpr const char* PrintedTextLength =
        "Длина напечатанного текста";
    static constexpr const char* DeletedSymbols = "Удалено символов";
    static constexpr const char* MistakePlaces = "Мест с ошибками";
    static constexpr const char* Mistakes = "Ошибок";
    static constexpr const char* MistakesPercent = "Процент ошибок";
    static constexpr const char* PrintedTextDuration =
        "Продолжительность напечатанного текста, сек";
    static constexpr const char* PrintedTextSpeed =
        "Скорость (реальная), знак/мин";
    static constexpr const char* MaxLikelihoodSpeed =
        "Скорость (несущая), знак/мин";
    static constexpr const char* Score = "Баллы";

    static constexpr const char* FullTextLengthHint =
        "Количество всех набранных символов с учетом удаленных";
    static constexpr const char* PrintedTextLengthHint =
        "Количество напечатанных символов без учета удаленных";
    static constexpr const char* DeletedSymbolsHint =
        "Количество удаленных символов";
    static constexpr const char* MistakePlacesHint =
        "Количество символов, на которых сделана ошибка (на одном символе "
        "можно стелать больше одной ошибки)";
    static constexpr const char* MistakesHint = "Количество сделаных ошибок";
    static constexpr const char* MistakesPercentHint =
        "Процент ошибок, вычисляется E/L*100, где E - количество ошибок, L - "
        "длина набранного текста (не включая удаленные символы)";
    static constexpr const char* PrintedTextDurationHint =
        "Время потраченное на набор текста, вычисляется как разность "
        "между временем нажатием последнего символа и первого символа";
    static constexpr const char* PrintedTextSpeedHint =
        "Средняя скорость, вычисляется как L/T, где L - длина напечатанного "
        "текста, T - продолжительность напечатанного текста";
    static constexpr const char* MaxLikelihoodSpeedHint =
        "Несущая скорость, эта скорость является точкой максимума для "
        "плотности распределения скорости (первый график)";
    static constexpr const char* ScoreHint =
        "Баллы начисляются за технику печати от 0 до 1, чем ближе к 1 тем "
        "лучше";
  };

  struct CTextModeView {
    static constexpr const char* TextMode = "Тексторвый режим";
    static constexpr const char* Raw = "Сырой";
    static constexpr const char* Full = "Полный";
    static constexpr const char* Printed = "Напечатанный";
    static constexpr const char* Non = "Нет";
    static constexpr const char* All = "Все";
    static constexpr const char* Essential = "Существенные";
    static constexpr const char* Shift = "Shift";
    static constexpr const char* Ctrl = "Ctrl";
    static constexpr const char* Alt = "Alt";
    static constexpr const char* Modifiers = "Модификаторы";

    static constexpr const char* RawHint =
        "Режим, в котором показываются все нажатые клавиши";
    static constexpr const char* FullHint =
        "Режим, в котором показывается набранный текст с учетом удаленных "
        "символов";
    static constexpr const char* PrintedHint =
        "Режим, в котором показывается набранный текст";
    static constexpr const char* NonHint =
        "Не отображать нажатия данной клавиши";
    static constexpr const char* AllHint =
        "Отображать все нажатия данной клавиши";
    static constexpr const char* EssentialHint =
        "Отображать только те нажатия, которые повлияли на текст в данном "
        "режиме";
  };

  struct CSpeedPlotter {
    static constexpr const char* PlotterTitle = "Плотность скорости";
    static constexpr const char* HorizontalAxisTitle = "Скорость, знаки/минута";
    static constexpr const char* Density1Name = "Плотность";
    static constexpr const char* Derivative1Name = "Производная";
    static constexpr const char* Density2Name = "Плотность М-Б";
    static constexpr const char* Derivative2Name = "Производная М-Б";
    static constexpr const char* Density3Name = "Плотность Р";
    static constexpr const char* Derivative3Name = "Производная Р";

    static constexpr const char* LegendHint =
        "Плотность распределения скорости - это \"непрерывная\" гистограмма "
        "для скорости.\n1) Плотность распределения "
        "восстанавливаемая с помощью нормального шума\n2) "
        "Производная плотности (1), нужна для лучшего понимания дефектов "
        "плотности\n3) Плотность распределения восстанавливаемая с "
        "помощью шума Максвела-Больцмана\n4) Производная плотности "
        "(3)\n5) Плотность восстанавливаемая с помощью шума "
        "Релея\n6) Производная плотности (5)";
  };

  struct CKeySchemePlotter {
    static constexpr const char* Title = "Клавишная схема";
    static constexpr const char* FingerAxisTitle = "Пальцы";
    static constexpr const char* TimeAxisTitle = "Время, мс";
    static constexpr const char* LeftThumb = "Левый большой";
    static constexpr const char* LeftIndex = "Левый указательный";
    static constexpr const char* LeftMiddle = "Левый средний";
    static constexpr const char* LeftRing = "Левый безымянный";
    static constexpr const char* LeftPinky = "Левый мизинец";
    static constexpr const char* RightThumb = "Правый большой";
    static constexpr const char* RightIndex = "Правый указательный";
    static constexpr const char* RightMiddle = "Правый средний";
    static constexpr const char* RightRing = "Правый безымянный";
    static constexpr const char* RightPinky = "Правый мизинец";
    static constexpr const char* Undefined = "Неопределен";
  };

  struct CFileMenu {
    static constexpr const char* Menu = "Файл";
    static constexpr const char* Save = "Сохранить";
    static constexpr const char* Load = "Загрузить";
  };
};

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CRUSLOCALE_H
