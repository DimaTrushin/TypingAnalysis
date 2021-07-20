#include "SeanceView.h"

#include <cassert>

#include <QTreeView>

namespace NSApplication {
namespace NSInterface {
namespace NSSeanceViewDetail {

CSeanceViewImpl::CSeanceViewImpl(QTreeView* TreeView)
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
                   this, &CSeanceViewImpl::onSelectionChanged);
}

CSeanceViewImpl::CSeanceObserver* CSeanceViewImpl::currentSeanceInput() {
  return &CurrentSeance_;
}

void CSeanceViewImpl::onSelectionChanged(int level, int index) {
  assert(index >= -1);
  qDebug() << "level =" << level << "index =" << index;
}

void CSeanceViewImpl::onCurrentSeanceConnect() {
  SeanceModel_.clear();
  if (CurrentSeance_.hasValue())
    SeanceModel_.appendFromSeance(*CurrentSeance_.data());
}

void CSeanceViewImpl::onCurrentSeanceNotify() {
  if (CurrentSeance_.hasValue())
    SeanceModel_.appendFromSeance(*CurrentSeance_.data());
  else
    SeanceModel_.clear();
}
} // namespace NSSeanceViewDetail

CSeanceView::CSeanceView(QTreeView* TreeView)
    : Impl_(std::make_unique<CSeanceViewImpl>(TreeView)) {
}

CSeanceView::CSeanceViewImpl* CSeanceView::operator->() const {
  return Impl_.get();
}

// namespace NSSeanceViewDetail

} // namespace NSInterface
} // namespace NSApplication
