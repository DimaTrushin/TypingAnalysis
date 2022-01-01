#include "SessionStatisticsModel.h"

namespace NSApplication {
namespace NSQt {

int CSessionStatisticsModel::rowCount(const QModelIndex& index) const {
  if (index.isValid())
    return 0;
  return static_cast<int>(Data_.size());
}

int CSessionStatisticsModel::columnCount(const QModelIndex& index) const {
  if (index.isValid())
    return 0;
  return 2;
}

QVariant CSessionStatisticsModel::data(const QModelIndex& index,
                                       int role) const {
  if (role != Qt::DisplayRole || !isValid(index))
    return QVariant();
  switch (index.column()) {
  case 0:
    return Data_[index.row()].Data;
  case 1:
    return Data_[index.row()].Value;
  default:
    return QVariant();
  }
}

QVariant CSessionStatisticsModel::headerData(int section,
                                             Qt::Orientation orientation,
                                             int role) const {
  if (!(orientation == Qt::Horizontal && role == Qt::DisplayRole))
    return QVariant();
  return headerName(section);
}

Qt::ItemFlags CSessionStatisticsModel::flags(const QModelIndex&) const {
  return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

bool CSessionStatisticsModel::clear() {
  if (Data_.size() == 0)
    return false;
  beginRemoveRows(QModelIndex(), 0, static_cast<int>(Data_.size() - 1));
  Data_.clear();
  endRemoveRows();
  return true;
}

bool CSessionStatisticsModel::setStatistics(CStatisticsDescription&& NewData) {
  clear();
  beginInsertRows(QModelIndex(), 0, static_cast<int>(NewData.size() - 1));
  Data_ = std::move(NewData);
  endInsertRows();
  return true;
}

void CSessionStatisticsModel::setLocale(const CLocalizer& Localizer) {
  DataName_ = Localizer.data();
  ValueName_ = Localizer.value();
  Q_EMIT headerDataChanged(Qt::Horizontal, 0, 1);
}

QString CSessionStatisticsModel::headerName(int column) const {
  switch (column) {
  case 0:
    return DataName_;
  case 1:
    return ValueName_;
  default:
    return "";
  }
}

bool CSessionStatisticsModel::isValid(const QModelIndex& index) const {
  return index.isValid() && index.column() < 2 &&
         size_t(index.row()) < Data_.size();
}

} // namespace NSQt
} // namespace NSApplication
