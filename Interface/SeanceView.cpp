#include "SeanceView.h"

#include <cassert>
#include <mutex>

#include <QTreeView>

namespace NSApplication {
namespace NSInterface {
namespace NSSeanceViewDetail {

CSeanceViewImpl::CSeanceViewImpl(QTreeView* TreeView)
    : TreeView_(TreeView),
      CurrentSeanceViewData_(
          [this](const CSeanceViewData& data) { onCurrentSeanceConnect(data); },
          [this](const CSeanceViewData& data) { onCurrentSeanceNotify(data); }),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }) {
  assert(TreeView_);
  TreeView_->setModel(this);
  TreeView_->expandAll();
  QObject::connect(TreeView_->selectionModel(),
                   &QItemSelectionModel::selectionChanged, this,
                   &CSeanceDescriptionModel::onSelectionChanged);
  QObject::connect(this, &CSeanceDescriptionModel::selectionChanged, this,
                   &CSeanceViewImpl::onSelectionChanged);
}

CSeanceViewImpl::CSeanceViewDataObserver*
CSeanceViewImpl::currentSeanceViewDataInput() {
  return &CurrentSeanceViewData_;
}

void CSeanceViewImpl::subscribeToSessionIndex(CIndexObserver* obs) {
  assert(obs);
  IndexOutput_.subscribe(obs);
}

CSeanceViewImpl::CLocalizerObserver* CSeanceViewImpl::localizerInput() {
  return &LocalizerInput_;
}

void CSeanceViewImpl::onSelectionChanged(int, int index) {
  assert(index >= -1);
  if (FromModel_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(MySignal_);
  IndexOutput_.set(index);
}

void CSeanceViewImpl::onCurrentSeanceConnect(const CSeanceViewData& data) {
  if (MySignal_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(FromModel_);
  clear();
  // TO DO
  // Need to
  // 1) add here a function to compute seance description to append
  // 2) pass the description to the Model
  // 3) make a separate object to make the description
  appendFromSeance(data.Seance);
  // Seems like I do not need these 4 lines
  if (data.CurrentSession >= 0)
    reselect(data.CurrentSession);
  else
    clearSelection();
}

void CSeanceViewImpl::onCurrentSeanceNotify(const CSeanceViewData& data) {
  if (MySignal_.isLocked())
    return;
  std::lock_guard<CSupressor> guard(FromModel_);
  appendFromSeance(data.Seance);
  // Seems like I do not need these 4 lines
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
  return TreeView_->selectionModel()->isSelected(IndexOfItem(row));
}

void CSeanceViewImpl::selectRow(int row) {
  TreeView_->selectionModel()->select(IndexOfItem(row),
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

} // namespace NSInterface
} // namespace NSApplication
