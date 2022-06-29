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

class CActions : public QObject {
  Q_OBJECT

  using CFilePathObserver = NSLibrary::CObserver<QString>;
  using CFilePathObservable = NSLibrary::CObservableData<QString>;

public:
  CActions(const CActionList& ActionList);

  void subscribeToFileSave(CFilePathObserver* obs);
  void subscribeToFileLoad(CFilePathObserver* obs);

public Q_SLOTS:
  void saveFile();
  void loadFile();

private:
  CFilePathObservable SaveFilePath_;
  CFilePathObservable LoadFilePath_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CACTIONS_H
