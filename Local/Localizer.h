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

private:
  template<class TTextModeViewLocale>
  CTextModeViewLocalizer(NSLocalizerDetail::Data<TTextModeViewLocale>)
      : TextMode_(TTextModeViewLocale::TextMode),
        Raw_(TTextModeViewLocale::Raw), Full_(TTextModeViewLocale::Full),
        Printed_(TTextModeViewLocale::Printed), Non_(TTextModeViewLocale::Non),
        All_(TTextModeViewLocale::All),
        Essential_(TTextModeViewLocale::Essential),
        Shift_(TTextModeViewLocale::Shift), Ctrl_(TTextModeViewLocale::Ctrl),
        Alt_(TTextModeViewLocale::Alt) {
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

  const CTextModeViewLocalizer& getTextModeViewLocalizer() const {
    return TextModeViewLocalizer_;
  }

private:
  template<class TLocale>
  CLocalizer(NSLocalizerDetail::Data<TLocale>)
      : SeanceViewLocalizer_(
            CSeanceViewLocalizer::make<TLocale::CSeanceView>()),
        TextModeViewLocalizer_(
            CTextModeViewLocalizer::make<TLocale::CTextModeView>()) {
  }
  CSeanceViewLocalizer SeanceViewLocalizer_;
  CTextModeViewLocalizer TextModeViewLocalizer_;
};

} // namespace NSLocal
} // namespace NSApplication

#endif // NSAPPLICATION_NSLOCAL_CLOCALIZER_H
