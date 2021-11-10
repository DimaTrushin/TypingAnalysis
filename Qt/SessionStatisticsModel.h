#ifndef NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H
#define NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H

#include <QAbstractTableModel>

#include "Kernel/TextData.h"
#include <deque>

namespace NSApplication {
namespace NSQt {

class CSessionStatisticsModel : public QAbstractTableModel {
  Q_OBJECT

  using CTextData = NSKernel::CTextData;

public:
  struct CDescription {
    QString Data;
    QString Value;
  };

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  bool clear();
  bool setStatistics(const CTextData&);

private:
  QString headerName(int column) const;

  bool isValid(const QModelIndex& index) const;

  static constexpr const char kDefaultDataName_[] = "Data";
  static constexpr const char kDefaultValueName_[] = "Value";

  std::deque<CDescription> Data_;
};

} // namespace NSQt
} // namespace NSApplication

#endif // NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H
