#include "LanguageMenu.h"

#include "Local/Languages.h"
#include <QMenu>

namespace NSApplication {
namespace NSInterface {
namespace NSLanguageMenuDetail {

CLanguageMenuImpl::CLanguageMenuImpl(QMenu* Menu) : Menu_(Menu) {
  assert(Menu_);
  setItemNames();
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

void CLanguageMenuImpl::setItemNames() {
  auto ActionList = Menu_->actions();
  assert(ActionList.size() == 2);
  ActionList[0]->setText(NSLocal::CLanguages::Lang[ELocale::Eng]);
  ActionList[1]->setText(NSLocal::CLanguages::Lang[ELocale::Rus]);
}

} // namespace NSLanguageMenuDetail
} // namespace NSInterface
} // namespace NSApplication
