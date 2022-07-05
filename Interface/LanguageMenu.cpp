#include "LanguageMenu.h"

#include <QMenu>

#include <QDebug>

namespace NSApplication {
namespace NSInterface {
namespace NSLanguageMenuDetail {

CLanguageMenuImpl::CLanguageMenuImpl(QMenu* Menu) : Menu_(Menu) {
  assert(Menu_);
  LocaleOutput_.set(ELocale::Eng);
  connect(Menu_, &QMenu::triggered, this,
          &CLanguageMenuImpl::onActionTriggered);
}

void CLanguageMenuImpl::subscribeToLocale(CLocaleObserver* obs) {
  assert(obs);
  LocaleOutput_.subscribe(obs);
}

void CLanguageMenuImpl::onActionTriggered(QAction* Action) {
  auto ActionList = Menu_->actions();
  int index = ActionList.indexOf(Action);
  assert(index >= 0 && index < ELocale::End);
  LocaleOutput_.set(static_cast<ELocale>(index));
}

} // namespace NSLanguageMenuDetail
} // namespace NSInterface
} // namespace NSApplication
