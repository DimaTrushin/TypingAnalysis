#include "SeanceView.h"

#include <cassert>

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

void CSeanceViewImpl::onSelectionChanged(int level, int index) {
  assert(index >= -1);
  qDebug() << "level =" << level << "index =" << index;
}

void CSeanceViewImpl::onCurrentSeanceConnect(const CSeanceViewData& data) {
  SeanceModel_.clear();
  SeanceModel_.appendFromSeance(data.Seance);
  // TO DO
  // add selection
}

void CSeanceViewImpl::onCurrentSeanceNotify(const CSeanceViewData& data) {
  if (CurrentSeanceViewData_.hasValue())
    SeanceModel_.appendFromSeance(data.Seance);
  else
    SeanceModel_.clear();
  // TO DO
  // add selection
}

} // namespace NSSeanceViewDetail

CSimpleSeanceView::CSimpleSeanceView(QTreeView* TreeView)
    : Impl_(std::make_unique<CSimpleSeanceViewImpl>(TreeView)) {
}

CSimpleSeanceView::CSimpleSeanceViewImpl*
CSimpleSeanceView::operator->() const {
  return Impl_.get();
}

CSeanceView::CSeanceView(QTreeView* TreeView)
    : Impl_(std::make_unique<CSeanceViewImpl>(TreeView)) {
}

CSeanceView::CSeanceViewImpl* CSeanceView::operator->() const {
  return Impl_.get();
}

// namespace NSSeanceViewDetail

} // namespace NSInterface
} // namespace NSApplication
