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
  };
};

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CRUSLOCALE_H
