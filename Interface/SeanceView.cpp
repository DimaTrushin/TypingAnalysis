#include "SeanceView.h"

#include <cassert>
#include <mutex>

#include <QTreeView>

namespace NSApplication {
namespace NSInterface {
namespace NSSeanceViewDetail {

CSimpleSeanceViewImpl::CSimpleSeanceViewImpl(QTreeView* TreeView)
    : TreeView_(TreeView),
      CurrentSeance_([this](CSeanceGetType) { onCurrentSeanceConnect(); },
                     [this](CSeanceGetType) { onCurrentSeanceNotify(); }) {
  assert(TreeView_);
  TreeView_->setModel(&SeanceModel_);
  TreeView_->expandAll();
  QObject::connect(TreeView_->selectionModel(),
                   &QItemSelectionModel::selectionChanged, &SeanceModel_,
                   &CSeanceDescriptionModel::onSelectionChanged);
  QObject::connect(&SeanceModel_, &CSeanceDescriptionModel::selectionChanged,
                   this, &CSimpleSeanceViewImpl::onSelectionChanged);
}

CSimpleSeanceViewImpl::CSeanceObserver*
CSimpleSeanceViewImpl::currentSeanceInput() {
  return &CurrentSeance_;
}

void CSimpleSeanceViewImpl::onSelectionChanged(int level, int index) {
  assert(index >= -1);
  qDebug() << "level =" << level << "index =" << index;
}

void CSimpleSeanceViewImpl::onCurrentSeanceConnect() {
  SeanceModel_.clear();
  if (CurrentSeance_.hasValue())
    SeanceModel_.appendFromSeance(*CurrentSeance_.data());
}

void CSimpleSeanceViewImpl::onCurrentSeanceNotify() {
  if (CurrentSeance_.hasValue())
    SeanceModel_.appendFromSeance(*CurrentSeance_.data());
  else
    SeanceModel_.clear();
}

CSeanceViewImpl::CSeanceViewImpl(QTreeView* TreeView)
    : TreeView_(TreeView),
      CurrentSeanceViewData_(
          [this](const CSeanceViewData& data) { onCurrentSeanceConnect(data); },
          [this](const CSeanceViewData& data) {
            onCurrentSeanceNotify(data);
          }) {
  assert(TreeView_);
  TreeView_->setModel(&SeanceModel_);
  TreeView_->expandAll();
  QObject::connect(TreeView_->selectionModel(),
                   &QItemSelectionModel::selectionChanged, &SeanceModel_,
                   &CSeanceDescriptionModel::onSelectionChanged);
  QObject::connect(&SeanceModel_, &CSeanceDescriptionModel::selectionChanged,
                   this, &CSeanceViewImpl::onSelectionChanged);
}

CSeanceViewImpl::CSeanceViewDataObserver*
CSeanceViewImpl::currentSeanceViewDataInput() {
  return &CurrentSeanceViewData_;
}

void CSeanceViewImpl::subscribeToSessionIndex(CIndexObserver* obs) {
  assert(obs);
  IndexOutput_.subscribe(obs);
}

void CSeanceViewImpl::onSelectionChanged(int level, int index) {
  assert(index >= -1);
  if (FromModel_.isLocked())
    return;
  qDebug() << "level =" << level << "index =" << index;
  std::lock_guard<CSupressor> guard(MySignal_);
  IndexOutput_.set(index);
}

void CSeanceViewImpl::onCurrentSeanceConnect(const CSeanceViewData& data) {
  if (MySignal_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(FromModel_);
  SeanceModel_.clear();
  SeanceModel_.appendFromSeance(data.Seance);
  if (data.CurrentSession >= 0)
    reselect(data.CurrentSession);
  else
    clearSelection();
}

void CSeanceViewImpl::onCurrentSeanceNotify(const CSeanceViewData& data) {
  if (MySignal_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(FromModel_);
  SeanceModel_.appendFromSeance(data.Seance);
  if (data.CurrentSession >= 0)
    reselect(data.CurrentSession);
  else
    clearSelection();
  // TO DO
  // It is a good question. Do I really want to clear the seance view?
  // Probably Yes but in the future
  // Then I should switch to CObserverHot
  //  } else
  //    SeanceModel_.clear();
}

bool CSeanceViewImpl::isRowSelected(int row) const {
  return TreeView_->selectionModel()->isSelected(SeanceModel_.IndexOfItem(row));
}

void CSeanceViewImpl::selectRow(int row) {
  TreeView_->selectionModel()->select(SeanceModel_.IndexOfItem(row),
                                      QItemSelectionModel::Rows |
                                          QItemSelectionModel::ClearAndSelect);
}

void CSeanceViewImpl::reselect(int row) {
  if (!isRowSelected(row))
    selectRow(row);
}

void CSeanceViewImpl::clearSelection() {
  TreeView_->selectionModel()->clearSelection();
}

} // namespace NSSeanceViewDetail

// namespace NSSeanceViewDetail

} // namespace NSInterface
} // namespace NSApplication
