#include "TextModeView.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>

#include <mutex>

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeViewDetail {

CTextModeViewImpl::CTextModeViewImpl(const CInitData& InitData)
    : TextModeGroup_(InitData.TextModeGroup),
      TextModeBox_(InitData.TextModeBox), Raw_(InitData.Raw),
      Full_(InitData.Full), Printed_(InitData.Printed),
      TextModeInput_([this](const CTextMode& Mode) { onTextModeInput(Mode); }),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }) {
  assert(TextModeGroup_);
  assert(TextModeBox_);
  assert(Raw_);
  assert(Full_);
  assert(Printed_);

  QObject::connect(TextModeGroup_, &QButtonGroup::idToggled, this,
                   &CTextModeViewImpl::TextButtonToggled);
}

CTextModeViewImpl::CTextModeObserver* CTextModeViewImpl::textModeInput() {
  return &TextModeInput_;
}

CTextModeViewImpl::CLocalizerObserver* CTextModeViewImpl::localizerInput() {
  return &LocalizerInput_;
}

void CTextModeViewImpl::subscribeToTextMode(CETextModeObserver* obs) {
  assert(obs);
  TextModeOutput_.subscribe(obs);
}

void CTextModeViewImpl::TextButtonToggled(int, bool checked) {
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

void CTextModeViewImpl::toggleAllButtons(CTextMode Mode) {
  toggleTextButton(getTextInt(Mode.TextMode));
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

CTextModeViewImpl::ETextMode CTextModeViewImpl::getCurrentTextMode() const {
  return getTextMode(TextModeGroup_->checkedId());
}

bool CTextModeViewImpl::areSwitchesInCorrectState() const {
  return TextModeGroup_->checkedId() != -1;
}

void CTextModeViewImpl::setLocale(const CLocalizer& Localizer) {
  TextModeBox_->setTitle(Localizer.textMode());
  Raw_->setText(Localizer.raw());
  Raw_->setToolTip(Localizer.rawHint());
  Full_->setText(Localizer.full());
  Full_->setToolTip(Localizer.fullHint());
  Printed_->setText(Localizer.printed());
  Printed_->setToolTip(Localizer.printedHint());
}

} // namespace NSTextModeViewDetail
} // namespace NSInterface
} // namespace NSApplication
