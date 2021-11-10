#include "SessionStatisticsModel.h"

#include <QDebug>

namespace NSApplication {
namespace NSQt {

int CSessionStatisticsModel::rowCount(const QModelIndex& index) const {
  if (index.isValid())
    return 0;
  return Data_.size();
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
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
}

bool CSessionStatisticsModel::clear() {
  if (Data_.size() == 0)
    return false;
  beginRemoveRows(QModelIndex(), 0, Data_.size() - 1);
  Data_.clear();
  endRemoveRows();
  return true;
}

bool CSessionStatisticsModel::setStatistics(const CTextData& Data) {
  clear();
  // TO DO
  // debug version
  beginInsertRows(QModelIndex(), 0, 8);
  Data_.clear();
  Data_.push_back(
      {"Places With Deletion",
       QString::number(Data.TextTree.get()->getNumberOfPlacesWithDeletion())});
  Data_.push_back(
      {"Deletion Series",
       QString::number(Data.TextTree.get()->getNumberOfDeletionSeries())});
  Data_.push_back(
      {"Deleted Symbols",
       QString::number(Data.TextTree.get()->getNumberOfDeletedSymbols())});
  Data_.push_back(
      {"Return Points",
       QString::number(Data.TextTree.get()->getNumberOfReturnPoints())});
  Data_.push_back(
      {"Tree size", QString::number(Data.TextTree.get()->getTreeSize())});
  Data_.push_back(
      {"Deletion Length Supremum",
       QString::number(
           Data.TextTree.get()->getDeletionSeriesLengthSupremum())});
  Data_.push_back(
      {"Mistake Places",
       QString::number(Data.TextTree.get()->getNumberOfMistakePlaces())});
  Data_.push_back(
      {"Mistake Routes",
       QString::number(Data.TextTree.get()->getNumberOfMistakeRoutes())});
  Data_.push_back(
      {"Mistake Route Length Supremum",
       QString::number(Data.TextTree.get()->getMistakeRoutesLengthSupremum())});
  endInsertRows();
  return false;
}

QString CSessionStatisticsModel::headerName(int column) const {
  switch (column) {
  case 0:
    return kDefaultDataName_;
  case 1:
    return kDefaultValueName_;
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
