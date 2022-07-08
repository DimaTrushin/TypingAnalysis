#include "SessionStatisticsModel.h"

namespace NSApplication {
namespace NSQt {

int CSessionStatisticsModel::rowCount(const QModelIndex& index) const {
  if (index.isValid())
    return 0;
  return size();
}

int CSessionStatisticsModel::columnCount(const QModelIndex& index) const {
  if (index.isValid())
    return 0;
  return 2;
}

QVariant CSessionStatisticsModel::data(const QModelIndex& index,
                                       int role) const {
  if (!isValid(index))
    return QVariant();
  if (role == Qt::DisplayRole)
    return getData(index.row(), index.column());
  if (role == Qt::ToolTipRole)
    return getHint(index.row(), index.column());
  return QVariant();
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
  if (size_ == 0)
    return false;
  beginRemoveRows(QModelIndex(), 0, size_ - 1);
  size_ = 0;
  endRemoveRows();
  return true;
}

bool CSessionStatisticsModel::printStatistics(
    const CStatisticsDescription& Data) {
  clear();
  beginInsertRows(QModelIndex(), 0, static_cast<int>(Data.size() - 1));
  size_ = static_cast<int>(Data.size());
  endInsertRows();
  return true;
}

void CSessionStatisticsModel::setLocale(const CLocalizer& Localizer) {
  DataName_ = Localizer.data();
  ValueName_ = Localizer.value();
  Q_EMIT headerDataChanged(Qt::Horizontal, 0, 1);
}

QVariant CSessionStatisticsModel::getData(int row, int column) const {
  switch (column) {
  case 0:
    return data_(row).Data;
  case 1:
    return data_(row).Value;
  default:
    return QVariant();
  }
}

QVariant CSessionStatisticsModel::getHint(int row, int) const {
  return data_(row).Hint;
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
  return index.isValid() && index.column() >= 0 && index.column() < 2 &&
         index.row() >= 0 && index.row() < size();
}

} // namespace NSQt
} // namespace NSApplication
