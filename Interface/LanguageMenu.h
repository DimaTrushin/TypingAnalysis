#ifndef NSAPPLICATION_NSINTERFACE_CLANGUAGEMENU_H
#define NSAPPLICATION_NSINTERFACE_CLANGUAGEMENU_H

#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/LocaleID.h"
#include "Local/Localizer.h"

#include <QObject>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSLanguageMenuDetail {

class CLanguageMenuImpl : public QObject {
  Q_OBJECT

  using ELocale = NSLocal::ELocale;
  using CLocaleObserver = NSLibrary::CObserver<ELocale>;
  using CLocaleObservable = NSLibrary::CObservableData<ELocale>;

public:
  CLanguageMenuImpl(QMenu* Menu);

  void subscribeToLocale(CLocaleObserver* obs);

public Q_SLOTS:
  void onActionTriggered(QAction* Action);

private:
  void setItems();
  void setItemNames();

  QMenu* Menu_;
  CLocaleObservable LocaleOutput_;
};
} // namespace NSLanguageMenuDetail

using CLanguageMenu =
    NSLibrary::CViewWrapper<NSLanguageMenuDetail::CLanguageMenuImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CLANGUAGEMENU_H
