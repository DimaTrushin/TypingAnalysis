#ifndef NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H
#define NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H

#include <QObject>

#include <memory>

#include "Kernel/SeanceViewData.h"
#include "Library/Observer2/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Library/StlExtension/Supressor.h"
#include "Local/Localizer.h"
#include "Qt/SeanceDescriptionModel.h"

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSSeanceViewDetail {

class CSeanceViewImpl : public NSQt::CSeanceDescriptionModel {
  Q_OBJECT
  using CSeanceDescriptionModel = NSQt::CSeanceDescriptionModel;

  using CSeance = NSKernel::CSeance;
  using CSeanceInput = NSLibrary::CHotInput<CSeance>;
  using CSeanceObserver = NSLibrary::CObserver<CSeance>;
  using CSeanceGetType = CSeanceObserver::CGetType;

  using CSeanceViewData = NSKernel::CSeanceViewData;
  using CSeanceViewDataInput = NSLibrary::CInput<CSeanceViewData>;
  using CSeanceViewDataObserver = NSLibrary::CObserver<CSeanceViewData>;
  //  using CSeanceViewDataGetType = CSeanceViewDataObserver::CGetType;

  using Index = NSKernel::CSeanceViewData::Index;
  using CIndexObserver = NSLibrary::CObserver<Index>;
  using CIndexObservable = NSLibrary::CObservableData<Index>;
  using CIndexGetType = CIndexObserver::CGetType;

  using CLocalizer = NSLocal::CSeanceViewLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

  using CSupressor = NSLibrary::CSupressor;

public:
  CSeanceViewImpl(QTreeView*);

  CSeanceViewDataObserver* currentSeanceViewDataInput();
  void subscribeToSessionIndex(CIndexObserver* obs);

  CLocalizerObserver* localizerInput();

public Q_SLOTS:
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
  CSeanceViewDataInput CurrentSeanceViewData_;
  CIndexObservable IndexOutput_;
  CLocalizerInput LocalizerInput_;
};

} // namespace NSSeanceViewDetail

using CSeanceView =
    NSLibrary::CViewWrapper<NSSeanceViewDetail::CSeanceViewImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSEANCEVIEW_H
