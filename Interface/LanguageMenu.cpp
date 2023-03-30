#include "LanguageMenu.h"

#include "Local/Languages.h"

#include <QMenu>

namespace NSApplication {
namespace NSInterface {
namespace NSLanguageMenuDetail {

CLanguageMenuImpl::CLanguageMenuImpl(QMenu* Menu) : Menu_(Menu) {
  assert(Menu_);
  setItems();
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

void CLanguageMenuImpl::setItems() {
  for (NSLocal::ELocaleType index = 0; index != NSLocal::ELocale::End; ++index)
    Menu_->addAction(new QAction(Menu_));
}

void CLanguageMenuImpl::setItemNames() {
  auto ActionList = Menu_->actions();
  for (NSLocal::ELocaleType index = 0; index != NSLocal::ELocale::End; ++index)
    ActionList[index]->setText(NSLocal::CLanguages::Lang[index]);
}

} // namespace NSLanguageMenuDetail
} // namespace NSInterface
} // namespace NSApplication
