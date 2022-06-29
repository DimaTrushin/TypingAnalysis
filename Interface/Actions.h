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

enum class EFileActionBlock { Activate, Deactivate };

class CActions : public QObject {
  Q_OBJECT

  using CFileActionObserver = NSLibrary::CObserver<CFileCommand>;
  using CFileActionObservable = NSLibrary::CObservableData<CFileCommand>;

  using CFileActionBlockObserver = NSLibrary::CObserver<EFileActionBlock>;
  using CFileActionBlockObservable =
      NSLibrary::CObservableData<EFileActionBlock>;

public:
  CActions(const CActionList& ActionList);

  void subscribeToFileAction(CFileActionObserver* obs);
  void subscribeToFileActionBlocker(CFileActionBlockObserver* obs);

public Q_SLOTS:
  void saveFile();
  void loadFile();

private:
  CFileActionObservable FileAction_;
  CFileActionBlockObservable FileActionBlocker_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CACTIONS_H
