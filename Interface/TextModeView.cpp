#include "TextModeView.h"

#include <QButtonGroup>
#include <QDebug>
#include <QRadioButton>

#include <mutex>

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeViewDetail {

CTextModeViewImpl::CTextModeViewImpl(QButtonGroup* TextButtonGroup,
                                     QButtonGroup* ShiftButtonGroup,
                                     QButtonGroup* CtrlButtonGroup,
                                     QButtonGroup* AltButtonGroup)
    : TextButtonGroup_(TextButtonGroup), ShiftButtonGroup_(ShiftButtonGroup),
      CtrlButtonGroup_(CtrlButtonGroup), AltButtonGroup_(AltButtonGroup),
      TextModeInput_([this](const CTextMode&) { onTextModeInput(); }) {
  assert(TextButtonGroup_);
  assert(ShiftButtonGroup_);
  assert(CtrlButtonGroup_);
  assert(AltButtonGroup_);
  QObject::connect(TextButtonGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::TextButtonToggled);
  QObject::connect(ShiftButtonGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::ShiftButtonToggled);
  QObject::connect(CtrlButtonGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::CtrlButtonToggled);
  QObject::connect(AltButtonGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::AltButtonToggled);
}

CTextModeViewImpl::CTextModeObserver* CTextModeViewImpl::textModeInput() {
  return &TextModeInput_;
}

void CTextModeViewImpl::subscribeToTextMode(CTextModeObserver* obs) {
  assert(obs);
  TextModeOutput_.subscribe(obs);
}

void CTextModeViewImpl::TextButtonToggled(int id, bool checked) {
  qDebug() << "TextButtonToggled id = " << id << "checked = " << checked;
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::ShiftButtonToggled(int id, bool checked) {
  qDebug() << "ShiftButtonToggled id = " << id << "checked = " << checked;
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::CtrlButtonToggled(int id, bool checked) {
  qDebug() << "CtrlButtonToggled id = " << id << "checked = " << checked;
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::AltButtonToggled(int id, bool checked) {
  qDebug() << "AltButtonToggled id = " << id << "checked = " << checked;
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::handleTextModeSwitchByGui() {
  if (FromModel_.isLocked())
    return;
  qDebug() << "handleTextModeSwitchByGui";
  std::lock_guard<CSupressor> guard(MySignal_);
  TextModeOutput_.set(getCurrentTextMode());
}

void CTextModeViewImpl::toggleTextButton(int id) {
  TextButtonGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleShiftButton(int id) {
  ShiftButtonGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleCtrlButton(int id) {
  CtrlButtonGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleAltButton(int id) {
  AltButtonGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleAllButtons(CTextMode Mode) {
  toggleTextButton(getTextInt(Mode.TextMode));
  toggleShiftButton(getModifierInt(Mode.ShiftMode));
  toggleCtrlButton(getModifierInt(Mode.CtrlMode));
  toggleAltButton(getModifierInt(Mode.AltMode));
}

CTextModeViewImpl::ETextMode CTextModeViewImpl::getTextMode(int Id) {
  switch (Id) {
  case 0:
    return ETextMode::Raw;
    break;
  case 1:
    return ETextMode::Full;
    break;
  case 2:
    return ETextMode::Printed;
    break;
  default:
    return ETextMode::NotDefined;
    break;
  }
}

CTextModeViewImpl::EModifierMode CTextModeViewImpl::getModifierMod(int Id) {
  switch (Id) {
  case 0:
    return EModifierMode::Non;
    break;
  case 1:
    return EModifierMode::All;
    break;
  case 2:
    return EModifierMode::Essential;
    break;
  default:
    return EModifierMode::NotDefined;
    break;
  }
}

int CTextModeViewImpl::getTextInt(ETextMode Mode) {
  switch (Mode) {
  case ETextMode::Raw:
    return 0;
    break;
  case ETextMode::Full:
    return 1;
    break;
  case ETextMode::Printed:
    return 2;
    break;
  default:
    return -1;
    break;
  }
}

int CTextModeViewImpl::getModifierInt(EModifierMode Mode) {
  switch (Mode) {
  case EModifierMode::Non:
    return 0;
    break;
  case EModifierMode::All:
    return 1;
    break;
  case EModifierMode::Essential:
    return 2;
    break;
  default:
    return -1;
    break;
  }
}

void CTextModeViewImpl::onTextModeInput() {
  if (MySignal_.isLocked())
    return;
  qDebug() << "onTextModeInput";
  std::lock_guard<CSupressor> guard(FromModel_);
  toggleAllButtons(*TextModeInput_.data());
}

CTextModeViewImpl::CTextMode CTextModeViewImpl::getCurrentTextMode() const {
  return {getTextMode(TextButtonGroup_->checkedId()),
          getModifierMod(ShiftButtonGroup_->checkedId()),
          getModifierMod(CtrlButtonGroup_->checkedId()),
          getModifierMod(AltButtonGroup_->checkedId())};
}
} // namespace NSTextModeViewDetail

CTextModeView::CTextModeView(QButtonGroup* TextButtonGroup,
                             QButtonGroup* ShiftButtonGroup,
                             QButtonGroup* CtrlButtonGroup,
                             QButtonGroup* AltButtonGroup)
    : Impl_(std::make_unique<CTextModeViewImpl>(
          TextButtonGroup, ShiftButtonGroup, CtrlButtonGroup, AltButtonGroup)) {
}

CTextModeView::CTextModeViewImpl* CTextModeView::operator->() const {
  return Impl_.get();
}

} // namespace NSInterface
} // namespace NSApplication
