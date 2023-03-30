#include "FileMenu.h"

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QString>

namespace NSApplication {
namespace NSInterface {

namespace NSFileMenuDetail {

CFileMenuImpl::CFileMenuImpl(QMenu* FileMenu)
    : Menu_(FileMenu), LocalizerInput_([this](const CLocalizer& Localizer) {
        setLocale(Localizer);
      }) {
  assert(Menu_);
  auto ActionList = Menu_->actions();
  assert(ActionList.size() == 2);
  connect(ActionList[0], &QAction::triggered, this, &CFileMenuImpl::saveFile);
  connect(ActionList[1], &QAction::triggered, this, &CFileMenuImpl::loadFile);
}

CFileMenuImpl::CLocalizerObserver* CFileMenuImpl::localizerInput() {
  return &LocalizerInput_;
}

void CFileMenuImpl::subscribeToFileAction(CFileActionObserver* obs) {
  FileAction_.subscribe(obs);
}

void CFileMenuImpl::subscribeToFileActionBlocker(
    CFileActionBlockObserver* obs) {
  FileActionBlocker_.subscribe(obs);
}

void CFileMenuImpl::saveFile() {
  FileActionBlocker_.set(EFileActionBlock::Deactivate);
  QString file = QFileDialog::getSaveFileName(nullptr, QString(), QString(),
                                              "TypingAnalysis (*.ta)");
  FileActionBlocker_.set(EFileActionBlock::Activate);

  // QWidget* parent,
  // Title "Save File",
  // default path "/home/jana/untitled.png",
  // filters tr("Images (*.png *.xpm *.jpg)"))

  if (file.isNull())
    return;
  FileAction_.set(CFileCommand{std::move(file), EFileAction::Save});
}

void CFileMenuImpl::loadFile() {
  FileActionBlocker_.set(EFileActionBlock::Deactivate);
  QString file = QFileDialog::getOpenFileName(
      nullptr, QString(), QString(), "TypingAnalysis (*.ta);;All (*.*)");
  FileActionBlocker_.set(EFileActionBlock::Activate);
  FileAction_.set(CFileCommand{std::move(file), EFileAction::Load});
}

void CFileMenuImpl::setLocale(const CLocalizer& Localizer) {
  Menu_->setTitle(Localizer.menu());
  auto ActionList = Menu_->actions();
  assert(ActionList.size() == 2);
  ActionList[0]->setText(Localizer.save());
  ActionList[1]->setText(Localizer.load());
}
} // namespace NSFileMenuDetail
} // namespace NSInterface
} // namespace NSApplication
