#ifndef NSAPPLICATION_NSINTERFACE_CFILEMENU_H
#define NSAPPLICATION_NSINTERFACE_CFILEMENU_H

#include <QObject>

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

enum class EFileAction { Save, Load };

struct CFileCommand {
  QString Path;
  EFileAction Action;
};

enum class EFileActionBlock { Activate, Deactivate };

namespace NSFileMenuDetail {

class CFileMenuImpl : public QObject {
  Q_OBJECT

  using CFileActionObserver = NSLibrary::CObserver<CFileCommand>;
  using CFileActionObservable = NSLibrary::CObservableData<CFileCommand>;

  using CFileActionBlockObserver = NSLibrary::CObserver<EFileActionBlock>;
  using CFileActionBlockObservable =
      NSLibrary::CObservableData<EFileActionBlock>;

public:
  explicit CFileMenuImpl(QMenu* FileMenu);

  void subscribeToFileAction(CFileActionObserver* obs);
  void subscribeToFileActionBlocker(CFileActionBlockObserver* obs);

public Q_SLOTS:
  void saveFile();
  void loadFile();

private:
  QMenu* Menu_;
  CFileActionObservable FileAction_;
  CFileActionBlockObservable FileActionBlocker_;
};
} // namespace NSFileMenuDetail

using CFileMenu = NSLibrary::CViewWrapper<NSFileMenuDetail::CFileMenuImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CFILEMENU_H
