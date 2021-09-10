#include "TextModuleOut.h"

#include "Kernel/TextModule/TextModuleGUI.h"

#include <QComboBox>
#include <QLabel>
#include <QObject>
#include <QTextEdit>

namespace NSApplication {

namespace NSInterface {

namespace NSTextModuleOutDetail {

CTextModuleOutImpl::CTextModuleOutImpl(CMainWindow* MainWindow)
    : ui_(std::make_unique<CTextModuleGUI>(MainWindow)),
      TextInput_([this](CQStringGetType Text) { setUpUI(Text); },
                 [this](CQStringGetType Text) { setUpUI(Text); }),
      TextModeOutput_([this]() -> CTextModeGetType { return TextMode_; }) {
  connectUI();
  synchronizeTextMode();
}

CTextModuleOutImpl::~CTextModuleOutImpl() = default;

void CTextModuleOutImpl::subscribeToTextMode(
    CTextModuleOutImpl::CTextModeObserver* Observer) {
  TextModeOutput_.subscribe(Observer);
}

CTextModuleOutImpl::CTextObserver* CTextModuleOutImpl::textInput() {
  return &TextInput_;
}

void CTextModuleOutImpl::connectUI() {
  QObject::connect(ui_->SelectionMenu(),
                   QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                   &CTextModuleOutImpl::updateTextMode);
}

void CTextModuleOutImpl::updateTextMode() {
  synchronizeTextMode();
  TextModeOutput_.notify();
}

void CTextModuleOutImpl::synchronizeTextMode() {
  TextMode_ = (CTextMode)ui_->SelectionMenu()->currentIndex();
}

void CTextModuleOutImpl::setUpUI(CQStringGetType Text) {
  if (Text.has_value()) {
    outputText(*Text);
  } else {
    outputEmptyCase();
  }
}

void CTextModuleOutImpl::outputText(const QString& Text) {
  ui_->Text()->setText(getOutputText(Text));
  ui_->setUpRegularCase();
}

void CTextModuleOutImpl::outputEmptyCase() {
  ui_->setUpEmptyCase();
  updateTextMode();
}

QString CTextModuleOutImpl::getOutputText(const QString& Text) {
  return QString("Text size = %1\n%2\n").arg(Text.size()).arg(Text);
}

} // namespace NSTextModuleOutDetail

namespace NSTextModuleOut {

CTextModuleOut::CTextModuleOut(CMainWindow* MainWindow)
    : Impl_(std::make_unique<CTextModuleOutImpl>(MainWindow)) {
}

CTextModuleOut::CTextModuleOutImpl* CTextModuleOut::operator->() {
  return Impl_.get();
}

} // namespace NSTextModuleOut

} // namespace NSInterface
} // namespace NSApplication
