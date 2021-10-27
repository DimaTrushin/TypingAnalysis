#ifndef NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H
#define NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H

#include <QObject>

#include <memory>

#include "Kernel/SeanceViewData.h"
#include "Library/Observer/Observer.h"
#include "SeanceDescriptionModel.h"

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSSeanceViewDetail {
class CSimpleSeanceViewImpl : public QObject {
  Q_OBJECT

  using CSeance = NSKernel::CSeance;
  using CSeanceInput = NSLibrary::CObserverHot<CSeance>;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;
  using CSeanceGetType = CSeanceObserver::CGetType;

public:
  CSimpleSeanceViewImpl(QTreeView*);

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

class CSeanceViewImpl : public QObject {
  Q_OBJECT

  using CSeance = NSKernel::CSeance;
  using CSeanceInput = NSLibrary::CObserverHot<CSeance>;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;
  using CSeanceGetType = CSeanceObserver::CGetType;

  using CSeanceViewData = NSKernel::CSeanceViewData;
  using CSeanceViewDataInput = NSLibrary::CObserverHotStrict<CSeanceViewData>;
  using CSeanceViewDataObserver = NSLibrary::CObserver<CSeanceViewData>;
  //  using CSeanceViewDataGetType = CSeanceViewDataObserver::CGetType;

public:
  CSeanceViewImpl(QTreeView*);

  CSeanceViewDataObserver* currentSeanceViewDataInput();

public slots:
  void onSelectionChanged(int level, int index);

private:
  void onCurrentSeanceConnect(const CSeanceViewData&);
  void onCurrentSeanceNotify(const CSeanceViewData&);

  QTreeView* TreeView_;
  CSeanceDescriptionModel SeanceModel_;
  CSeanceViewDataInput CurrentSeanceViewData_;
};

} // namespace NSSeanceViewDetail

class CSimpleSeanceView {
  using CSimpleSeanceViewImpl = NSSeanceViewDetail::CSimpleSeanceViewImpl;

public:
  CSimpleSeanceView(QTreeView*);

  CSimpleSeanceViewImpl* operator->() const;

private:
  std::unique_ptr<CSimpleSeanceViewImpl> Impl_;
};

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
