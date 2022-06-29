#ifndef NSAPPLICATION_NSINTERFACE_CACTIONS_H
#define NSAPPLICATION_NSINTERFACE_CACTIONS_H

#include <QObject>

#include "Library/Observer/Observer.h"

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

struct CActionList {
  QAction* saveFile;
  QAction* loadFile;
};

enum class EFileAction { Save, Load };

struct CFileCommand {
  QString Path;
  EFileAction Action;
};

class CActions : public QObject {
  Q_OBJECT

  using CFileActionObserver = NSLibrary::CObserver<CFileCommand>;
  using CFileActionObservable = NSLibrary::CObservableData<CFileCommand>;

public:
  CActions(const CActionList& ActionList);

  void subscribeToFileAction(CFileActionObserver* obs);

public Q_SLOTS:
  void saveFile();
  void loadFile();

private:
  CFileActionObservable FileAction_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CACTIONS_H
