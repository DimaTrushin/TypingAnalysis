#ifndef NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H
#define NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H

#include <QObject>

#include <memory>

#include "Kernel/Seance.h"
#include "Library/Observer/Observer.h"
#include "SeanceDescriptionModel.h"

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSSeanceViewDetail {
class CSeanceViewImpl : public QObject {
  Q_OBJECT

  using CSeance = NSKernel::CSeance;
  using CSeanceInput = NSLibrary::CObserverHot<CSeance>;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;
  using CSeanceGetType = CSeanceObserver::CGetType;

public:
  CSeanceViewImpl(QTreeView*);

  CSeanceObserver* currentSeanceInput();

public slots:
  void onSelectionChanged(int level, int index);

private:
  void onCurrentSeanceConnect();
  void onCurrentSeanceNotify();

  QTreeView* TreeView_;
  CSeanceDescriptionModel SeanceModel_;
  CSeanceInput CurrentSeance_;
};
} // namespace NSSeanceViewDetail

class CSeanceView {
  using CSeanceViewImpl = NSSeanceViewDetail::CSeanceViewImpl;

public:
  CSeanceView(QTreeView*);

  CSeanceViewImpl* operator->() const;

private:
  std::unique_ptr<CSeanceViewImpl> Impl_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H
