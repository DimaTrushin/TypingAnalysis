#include "ModifiersMenu.h"

#include <QMenu>
#include <mutex>

namespace NSApplication {
namespace NSInterface {
namespace NSModifiersMenuDetail {

CModifiersMenuImpl::CModifiersMenuImpl(const CInitData& InitData)
    : Menu_(InitData.Menu), ShiftMenu_(InitData.ShiftMenu),
      CtrlMenu_(InitData.CtrlMenu), AltMenu_(InitData.AltMenu),
      ModifiersInput_([this](const CTextMode& Mode) {
        handleModifiersMode(Mode.Modifiers);
      }),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }) {
  assert(Menu_);
  assert(ShiftMenu_);
  assert(CtrlMenu_);
  assert(AltMenu_);

  connectShiftMenu();
  connectCtrlMenu();
  connectAltMenu();
}

CModifiersMenuImpl::CTextModeObserver* CModifiersMenuImpl::modifersModeInput() {
  return &ModifiersInput_;
}

CModifiersMenuImpl::CLocalizerObserver* CModifiersMenuImpl::localizerInput() {
  return &LocalizerInput_;
}

void CModifiersMenuImpl::subscribeToModifiersMode(CModifiersModeObserver* obs) {
  ModifiersOutput_.subscribe(obs);
}

void CModifiersMenuImpl::shiftNonToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{EModifiersMode::Non, getCtrlMode(), getAltMode()});
}

void CModifiersMenuImpl::shiftAllToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{EModifiersMode::All, getCtrlMode(), getAltMode()});
}

void CModifiersMenuImpl::shiftEssentialToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{EModifiersMode::Essential, getCtrlMode(), getAltMode()});
}

void CModifiersMenuImpl::ctrlNonToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{getShiftMode(), EModifiersMode::Non, getAltMode()});
}

void CModifiersMenuImpl::ctrlAllToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{getShiftMode(), EModifiersMode::All, getAltMode()});
}

void CModifiersMenuImpl::ctrlEssentialToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{getShiftMode(), EModifiersMode::Essential, getAltMode()});
}

void CModifiersMenuImpl::altNonToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{getShiftMode(), getCtrlMode(), EModifiersMode::Non});
}

void CModifiersMenuImpl::altAllToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{getShiftMode(), getCtrlMode(), EModifiersMode::All});
}

void CModifiersMenuImpl::altEssentialToggled(bool checked) {
  if (!checked)
    return;
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  ModifiersOutput_.set(
      CModifiersMode{getShiftMode(), getCtrlMode(), EModifiersMode::Essential});
}

void CModifiersMenuImpl::connectShiftMenu() {
  auto ActionList = ShiftMenu_->actions();
  assert(ActionList.size() == 3);
  connect(ActionList[0], &QAction::toggled, this,
          &CModifiersMenuImpl::shiftNonToggled);
  connect(ActionList[1], &QAction::toggled, this,
          &CModifiersMenuImpl::shiftAllToggled);
  connect(ActionList[2], &QAction::toggled, this,
          &CModifiersMenuImpl::shiftEssentialToggled);
}

void CModifiersMenuImpl::connectCtrlMenu() {
  auto ActionList = CtrlMenu_->actions();
  assert(ActionList.size() == 3);
  connect(ActionList[0], &QAction::toggled, this,
          &CModifiersMenuImpl::ctrlNonToggled);
  connect(ActionList[1], &QAction::toggled, this,
          &CModifiersMenuImpl::ctrlAllToggled);
  connect(ActionList[2], &QAction::toggled, this,
          &CModifiersMenuImpl::ctrlEssentialToggled);
}

void CModifiersMenuImpl::connectAltMenu() {
  auto ActionList = AltMenu_->actions();
  assert(ActionList.size() == 3);
  connect(ActionList[0], &QAction::toggled, this,
          &CModifiersMenuImpl::altNonToggled);
  connect(ActionList[1], &QAction::toggled, this,
          &CModifiersMenuImpl::altAllToggled);
  connect(ActionList[2], &QAction::toggled, this,
          &CModifiersMenuImpl::altEssentialToggled);
}

void CModifiersMenuImpl::handleModifiersMode(const CModifiersMode& Mode) {
  if (MySignal_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(FromModel_);

  handleShiftMode(Mode.ShiftMode);
  handleCtrlMode(Mode.CtrlMode);
  handleAltMode(Mode.AltMode);
}

void CModifiersMenuImpl::handleShiftMode(EModifiersMode Mode) {
  auto ActionList = ShiftMenu_->actions();
  switch (Mode) {
  case EModifiersMode::Non:
    ActionList[0]->setChecked(true);
    break;
  case EModifiersMode::All:
    ActionList[1]->setChecked(true);
    break;
  case EModifiersMode::Essential:
    ActionList[2]->setChecked(true);
    break;
  default:
    break;
  }
}

void CModifiersMenuImpl::handleCtrlMode(EModifiersMode Mode) {
  auto ActionList = CtrlMenu_->actions();
  switch (Mode) {
  case EModifiersMode::Non:
    ActionList[0]->setChecked(true);
    break;
  case EModifiersMode::All:
    ActionList[1]->setChecked(true);
    break;
  case EModifiersMode::Essential:
    ActionList[2]->setChecked(true);
    break;
  default:
    break;
  }
}

void CModifiersMenuImpl::handleAltMode(EModifiersMode Mode) {
  auto ActionList = AltMenu_->actions();
  switch (Mode) {
  case EModifiersMode::Non:
    ActionList[0]->setChecked(true);
    break;
  case EModifiersMode::All:
    ActionList[1]->setChecked(true);
    break;
  case EModifiersMode::Essential:
    ActionList[2]->setChecked(true);
    break;
  default:
    break;
  }
}

void CModifiersMenuImpl::setLocale(const CLocalizer& Localizer) {
  Menu_->setTitle(Localizer.modifiers());
  setShiftLocale(Localizer);
  setCtrlLocale(Localizer);
  setAltLocale(Localizer);
}

void CModifiersMenuImpl::setShiftLocale(const CLocalizer& Localizer) {
  ShiftMenu_->setTitle(Localizer.shift());
  localizerMenuItems(Localizer, ShiftMenu_);
}

void CModifiersMenuImpl::setCtrlLocale(const CLocalizer& Localizer) {
  CtrlMenu_->setTitle(Localizer.ctrl());
  localizerMenuItems(Localizer, CtrlMenu_);
}

void CModifiersMenuImpl::setAltLocale(const CLocalizer& Localizer) {
  AltMenu_->setTitle(Localizer.alt());
  localizerMenuItems(Localizer, AltMenu_);
}

void CModifiersMenuImpl::localizerMenuItems(const CLocalizer& Localizer,
                                            QMenu* Menu) {
  auto ActionList = Menu->actions();
  assert(ActionList.size() == 3);
  ActionList[0]->setText(Localizer.non());
  ActionList[1]->setText(Localizer.all());
  ActionList[2]->setText(Localizer.essential());
}

CModifiersMenuImpl::EModifiersMode CModifiersMenuImpl::getShiftMode() const {
  return getMode(ShiftMenu_);
}

CModifiersMenuImpl::EModifiersMode CModifiersMenuImpl::getCtrlMode() const {
  return getMode(CtrlMenu_);
}

CModifiersMenuImpl::EModifiersMode CModifiersMenuImpl::getAltMode() const {
  return getMode(AltMenu_);
}

CModifiersMenuImpl::EModifiersMode CModifiersMenuImpl::getMode(QMenu* Menu) {
  auto ActionList = Menu->actions();
  assert(ActionList.size() == 3);
  if (ActionList[0]->isChecked())
    return EModifiersMode::Non;
  if (ActionList[1]->isChecked())
    return EModifiersMode::All;
  return EModifiersMode::Essential;
}

} // namespace NSModifiersMenuDetail
} // namespace NSInterface
} // namespace NSApplication
