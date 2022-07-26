#include "SeanceDescriptionModel.h"

#include "Kernel/Seance.h"

namespace NSApplication {
namespace NSQt {

QModelIndex CSeanceDescriptionModel::IndexOfItem(int row) const {
  return index(row, 0, index(0, 0));
}

QModelIndex CSeanceDescriptionModel::index(int row, int column,
                                           const QModelIndex& parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();
  switch (get_level(parent)) {
  case -1:
    assert(row == 0 && "row must be zero here!");
    return createIndex(row, column, make_level(0));
  case 0:
    assert(row >= 0 && row < size() && "row must be in bounds!");
    return createIndex(row, column, make_level(1));
  case 1:
    assert(false && "This must never happen!");
  default:;
  }
  return QModelIndex();
}

QModelIndex CSeanceDescriptionModel::parent(const QModelIndex& child) const {
  switch (get_level(child)) {
  case -1:
  case 0:
    return QModelIndex();
  case 1:
    return index(0, 0);
  default:;
  }
  return QModelIndex();
}

int CSeanceDescriptionModel::rowCount(const QModelIndex& parent) const {
  switch (get_level(parent)) {
  case -1:
    return 1;
  case 0:
    return size();
  case 1:
    return 0;
  default:;
  }
  return 0;
}

int CSeanceDescriptionModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent)
  return 2;
}

QVariant CSeanceDescriptionModel::data(const QModelIndex& index,
                                       int role) const {
  if (role != Qt::DisplayRole)
    return QVariant();
  switch (get_level(index)) {
  case -1:
    return QVariant();
  case 0:
    if (index.column() == 0)
      return currentSeanceName();
    return size();
  case 1:
    return get_regular_data(index.row(), index.column());
  default:;
  }
  return QVariant();
}

QVariant CSeanceDescriptionModel::headerData(int section,
                                             Qt::Orientation orientation,
                                             int role) const {
  if (!(orientation == Qt::Horizontal && role == Qt::DisplayRole))
    return QVariant();
  return headerName(section);
}

Qt::ItemFlags CSeanceDescriptionModel::flags(const QModelIndex& index) const {
  switch (get_level(index)) {
  case -1:
  case 0:
    return Qt::NoItemFlags;
  case 1:
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
  default:;
  }
  return Qt::NoItemFlags;
}

bool CSeanceDescriptionModel::appendFromSeance(const CSeance& Seance) {
  assert(Seance.size() >= Data_.size());
  if (Seance.size() == Data_.size())
    return false;
  beginInsertRows(createIndex(0, 0, make_level(0)), size(),
                  static_cast<int>(Seance.size()) - 1);
  auto iter = Seance.begin() + Data_.size();
  while (iter != Seance.end()) {
    Data_.emplace_back(
        CDescription{getSessionDescription(*iter), iter->size()});
    ++iter;
  }
  endInsertRows();
  assert(Seance.size() == Data_.size());
  return true;
}

bool CSeanceDescriptionModel::clear() {
  if (size() == 0)
    return false;
  beginRemoveRows(createIndex(0, 0, make_level(0)), 0, size() - 1);
  Data_.clear();
  endRemoveRows();
  return true;
}

void CSeanceDescriptionModel::setLocale(const CLocalizer& Localizer) {
  Description_ = Localizer.description();
  Size_ = Localizer.size();
  Q_EMIT headerDataChanged(Qt::Horizontal, 0, 1);
  CurrentSeance_ = Localizer.currentSeance();
  Q_EMIT dataChanged(createIndex(0, 0, make_level(0)),
                     createIndex(0, 0, make_level(0)));
}

void CSeanceDescriptionModel::onSelectionChanged(
    const QItemSelection& selected, const QItemSelection& deselected) {
  Q_UNUSED(deselected);
  auto IndexList = selected.indexes();
  if (IndexList.size() > 0) {
    auto Index = IndexList.at(0);
    assert(get_level(Index) == 1);
    Q_EMIT selectionChanged(get_level(Index), Index.row());
  } else {
    Q_EMIT selectionChanged(-1, -1);
  }
}

int CSeanceDescriptionModel::get_level(const QModelIndex& index) const {
  if (!index.isValid())
    return -1;
  return static_cast<char*>(index.internalPointer()) -
         static_cast<char*>(nullptr);
}

void* CSeanceDescriptionModel::make_level(int level) const {
  if (level < 0)
    return nullptr;
  return static_cast<char*>(nullptr) + level;
}

int CSeanceDescriptionModel::size() const {
  return static_cast<int>(Data_.size());
}

QVariant CSeanceDescriptionModel::get_regular_data(int row, int column) const {
  if (row < 0 || row >= size())
    return QVariant();
  if (column == 0)
    return Data_[row].Text;
  return Data_[row].Size;
}

QString CSeanceDescriptionModel::currentSeanceName() const {
  return CurrentSeance_;
}

QString CSeanceDescriptionModel::headerName(int column) const {
  switch (column) {
  case 0:
    return Description_;
  case 1:
    return Size_;
  default:
    return "";
  }
}

QString
CSeanceDescriptionModel::getSessionDescription(const CSession& Session) const {
  // TO DO
  // This is for debug purpose only
  // Need to create a DescriptionMaker
  static constexpr const size_t kDescriptionSize = 15;
  size_t size = std::min(Session.size(), kDescriptionSize);
  QString Description;
  for (size_t index = 0; index < size; ++index) {
    Description.append(Session[index].getRawSymbol());
  }
  return Description;
}

} // namespace NSQt
} // namespace NSApplication
