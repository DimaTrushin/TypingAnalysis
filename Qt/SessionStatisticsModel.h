#ifndef NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H
#define NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H

#include <QAbstractTableModel>

#include "Kernel/TextData.h"
#include "Local/Localizer.h"

#include <deque>

namespace NSApplication {
namespace NSQt {

class CSessionStatisticsModel : public QAbstractTableModel {
  Q_OBJECT

  using CTextData = NSKernel::CTextData;
  using CLocalizer = NSLocal::CStatisticsViewLocalizer;

public:
  struct CDescription {
    QString Data;
    QString Value;
  };
  using CStatisticsDescription = std::deque<CDescription>;

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  bool clear();
  bool setStatistics(CStatisticsDescription&&);
  void setLocale(const CLocalizer& Localizer);

private:
  QString headerName(int column) const;

  bool isValid(const QModelIndex& index) const;

  QString DataName_;
  QString ValueName_;

  CStatisticsDescription Data_;
};

} // namespace NSQt
} // namespace NSApplication

#endif // NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H
