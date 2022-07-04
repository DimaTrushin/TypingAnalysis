#include "TextModeView.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>

#include <mutex>

#include <QDebug>

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeViewDetail {

CTextModeViewImpl::CTextModeViewImpl(const CInitData& InitData)
    : TextModeGroup_(InitData.TextModeGroup),
      TextModeBox_(InitData.TextModeBox), Raw_(InitData.Raw),
      Full_(InitData.Full), Printed_(InitData.Printed),
      ShiftGroup_(InitData.ShiftGroup), ShiftBox_(InitData.ShiftBox),
      ShiftNon_(InitData.ShiftNon), ShiftAll_(InitData.ShiftAll),
      ShiftEssential_(InitData.ShiftEssential), CtrlGroup_(InitData.CtrlGroup),
      CtrlBox_(InitData.CtrlBox), CtrlNon_(InitData.CtrlNon),
      CtrlAll_(InitData.CtrlAll), CtrlEssential_(InitData.CtrlEssential),
      AltGroup_(InitData.AltGroup), AltBox_(InitData.AltBox),
      AltNon_(InitData.AltNon), AltAll_(InitData.AltAll),
      AltEssential_(InitData.AltEssential),
      TextModeInput_([this](const CTextMode& Mode) { onTextModeInput(Mode); }),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }) {
  assert(TextModeGroup_);
  assert(TextModeBox_);
  assert(Raw_);
  assert(Full_);
  assert(Printed_);

  assert(ShiftGroup_);
  assert(ShiftBox_);
  assert(ShiftNon_);
  assert(ShiftAll_);
  assert(ShiftEssential_);

  assert(CtrlGroup_);
  assert(CtrlBox_);
  assert(CtrlNon_);
  assert(CtrlAll_);
  assert(CtrlEssential_);

  assert(AltGroup_);
  assert(AltBox_);
  assert(AltNon_);
  assert(AltAll_);
  assert(AltEssential_);

  QObject::connect(TextModeGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::TextButtonToggled);
  QObject::connect(ShiftGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::ShiftButtonToggled);
  QObject::connect(CtrlGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::CtrlButtonToggled);
  QObject::connect(AltGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::AltButtonToggled);
}

CTextModeViewImpl::CTextModeObserver* CTextModeViewImpl::textModeInput() {
  return &TextModeInput_;
}

CTextModeViewImpl::CLocalizerObserver* CTextModeViewImpl::localizerInput() {
  return &LocalizerInput_;
}

void CTextModeViewImpl::subscribeToTextMode(CTextModeObserver* obs) {
  assert(obs);
  TextModeOutput_.subscribe(obs);
}

void CTextModeViewImpl::TextButtonToggled(int, bool checked) {
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::ShiftButtonToggled(int, bool checked) {
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::CtrlButtonToggled(int, bool checked) {
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::AltButtonToggled(int, bool checked) {
  if (!checked)
    return;
  handleTextModeSwitchByGui();
}

void CTextModeViewImpl::handleTextModeSwitchByGui() {
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  if (areSwitchesInCorrectState())
    TextModeOutput_.set(getCurrentTextMode());
}

void CTextModeViewImpl::toggleTextButton(int id) {
  TextModeGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleShiftButton(int id) {
  ShiftGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleCtrlButton(int id) {
  CtrlGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleAltButton(int id) {
  AltGroup_->button(id)->toggle();
}

void CTextModeViewImpl::toggleAllButtons(CTextMode Mode) {
  toggleTextButton(getTextInt(Mode.TextMode));
  toggleShiftButton(getModifierInt(Mode.Modifiers.ShiftMode));
  toggleCtrlButton(getModifierInt(Mode.Modifiers.CtrlMode));
  toggleAltButton(getModifierInt(Mode.Modifiers.AltMode));
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
    assert(false);
    return ETextMode::Raw;
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
    assert(false);
    return EModifierMode::Non;
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
    assert(false);
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

void CTextModeViewImpl::onTextModeInput(const CTextMode& Mode) {
  if (MySignal_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(FromModel_);
  toggleAllButtons(Mode);
}

CTextModeViewImpl::CTextMode CTextModeViewImpl::getCurrentTextMode() const {
  return {getTextMode(TextModeGroup_->checkedId()),
          {getModifierMod(ShiftGroup_->checkedId()),
           getModifierMod(CtrlGroup_->checkedId()),
           getModifierMod(AltGroup_->checkedId())}};
}

bool CTextModeViewImpl::areSwitchesInCorrectState() const {
  return TextModeGroup_->checkedId() != -1 && ShiftGroup_->checkedId() != -1 &&
         CtrlGroup_->checkedId() != -1 && AltGroup_->checkedId() != -1;
}

void CTextModeViewImpl::setLocale(const CLocalizer& Localizer) {
  TextModeBox_->setTitle(Localizer.textMode());
  Raw_->setText(Localizer.raw());
  Full_->setText(Localizer.full());
  Printed_->setText(Localizer.printed());

  ShiftBox_->setTitle(Localizer.shift());
  ShiftNon_->setText(Localizer.non());
  ShiftAll_->setText(Localizer.all());
  ShiftEssential_->setText(Localizer.essential());

  CtrlBox_->setTitle(Localizer.ctrl());
  CtrlNon_->setText(Localizer.non());
  CtrlAll_->setText(Localizer.all());
  CtrlEssential_->setText(Localizer.essential());

  AltBox_->setTitle(Localizer.alt());
  AltNon_->setText(Localizer.non());
  AltAll_->setText(Localizer.all());
  AltEssential_->setText(Localizer.essential());
}
} // namespace NSTextModeViewDetail
} // namespace NSInterface
} // namespace NSApplication
