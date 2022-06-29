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

void CActions::subscribeToFileSave(CFilePathObserver* obs) {
  SaveFilePath_.subscribe(obs);
}

void CActions::subscribeToFileLoad(CFilePathObserver* obs) {
  LoadFilePath_.subscribe(obs);
}

void CActions::saveFile() {
  // Need to block keyboard interseption here
  QString file = QFileDialog::getSaveFileName(nullptr, QString(), QString(),
                                              "TypingAnalysis (*.ta)");
  // Need to unblock keyboard interseption here

  // QWidget* parent,
  // Title "Save File",
  // default path "/home/jana/untitled.png",
  // filters tr("Images (*.png *.xpm *.jpg)"))

  if (file.isNull())
    return;
  SaveFilePath_.set(std::move(file));
}

void CActions::loadFile() {
  // Need to block keyboard interseption here
  QString file = QFileDialog::getOpenFileName(
      nullptr, QString(), QString(), "TypingAnalysis (*.ta);;All (*.*)");
  // Need to unblock keyboard interseption here
  LoadFilePath_.set(std::move(file));
}

} // namespace NSInterface
} // namespace NSApplication
