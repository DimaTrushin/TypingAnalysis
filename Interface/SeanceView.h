#ifndef NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H
#define NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H

#include <QObject>

#include <memory>

#include "Kernel/SeanceViewData.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Library/StlExtension/Supressor.h"
#include "Qt/SeanceDescriptionModel.h"

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSSeanceViewDetail {
class CSimpleSeanceViewImpl : public QObject {
  Q_OBJECT
  using CSeanceDescriptionModel = NSQt::CSeanceDescriptionModel;

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
  using CSeanceDescriptionModel = NSQt::CSeanceDescriptionModel;

  using CSeance = NSKernel::CSeance;
  using CSeanceInput = NSLibrary::CObserverHot<CSeance>;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;
  using CSeanceGetType = CSeanceObserver::CGetType;

  using CSeanceViewData = NSKernel::CSeanceViewData;
  using CSeanceViewDataInput = NSLibrary::CObserverHotStrict<CSeanceViewData>;
  using CSeanceViewDataObserver = NSLibrary::CObserver<CSeanceViewData>;
  //  using CSeanceViewDataGetType = CSeanceViewDataObserver::CGetType;

  using Index = NSKernel::CSeanceViewData::Index;
  using CIndexObserver = NSLibrary::CObserver<Index>;
  using CIndexObservable = NSLibrary::CObservableData<Index>;
  using CIndexGetType = CIndexObserver::CGetType;

  using CSupressor = NSLibrary::CSupressor;

public:
  CSeanceViewImpl(QTreeView*);

  CSeanceViewDataObserver* currentSeanceViewDataInput();
  void subscribeToSessionIndex(CIndexObserver* obs);

public slots:
  void onSelectionChanged(int level, int index);

private:
  void onCurrentSeanceConnect(const CSeanceViewData&);
  void onCurrentSeanceNotify(const CSeanceViewData&);

  bool isRowSelected(int) const;
  void selectRow(int);
  void reselect(int);
  void clearSelection();

  CSupressor FromModel_;
  CSupressor MySignal_;
  QTreeView* TreeView_;
  CSeanceDescriptionModel SeanceModel_;
  CSeanceViewDataInput CurrentSeanceViewData_;
  CIndexObservable IndexOutput_;
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

using CSeanceView =
    NSLibrary::CViewWrapper<NSSeanceViewDetail::CSeanceViewImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H
