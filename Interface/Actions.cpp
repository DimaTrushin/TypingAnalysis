#include "Actions.h"
#include <QAction>
#include <QFileDialog>
#include <QString>

namespace NSApplication {
namespace NSInterface {

CActions::CActions(const CActionList& ActionList) {
  connect(ActionList.saveFile, &QAction::triggered, this, &CActions::saveFile);
  connect(ActionList.loadFile, &QAction::triggered, this, &CActions::loadFile);
}

void CActions::subscribeToFileAction(CFileActionObserver* obs) {
  FileAction_.subscribe(obs);
}

void CActions::subscribeToFileActionBlocker(CFileActionBlockObserver* obs) {
  FileActionBlocker_.subscribe(obs);
}

void CActions::saveFile() {
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

void CActions::loadFile() {
  FileActionBlocker_.set(EFileActionBlock::Deactivate);
  QString file = QFileDialog::getOpenFileName(
      nullptr, QString(), QString(), "TypingAnalysis (*.ta);;All (*.*)");
  FileActionBlocker_.set(EFileActionBlock::Activate);
  FileAction_.set(CFileCommand{std::move(file), EFileAction::Load});
}

} // namespace NSInterface
} // namespace NSApplication
