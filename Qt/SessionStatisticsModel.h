#ifndef NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H
#define NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H

#include <QAbstractTableModel>

#include "Kernel/StatisticsDescription.h"
#include "Kernel/TextData.h"
#include "Local/Localizer.h"

#include <deque>

namespace NSApplication {
namespace NSQt {

class CSessionStatisticsModel : public QAbstractTableModel {
  Q_OBJECT

  using CTextData = NSKernel::CTextData;
  using CLocalizer = NSLocal::CStatisticsViewLocalizer;

  using CDescription = NSKernel::CDescription;
  using CStatisticsDescription = NSKernel::CStatisticsDescription;

public:
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  bool clear();
  bool printStatistics(const CStatisticsDescription&);
  void setLocale(const CLocalizer& Localizer);

private:
  QVariant getData(int row, int column) const;
  QVariant getHint(int row, int column) const;

  QString headerName(int column) const;

  bool isValid(const QModelIndex& index) const;

  virtual int size() const = 0;
  virtual const CDescription& data_(int row) const = 0;

  QString DataName_;
  QString ValueName_;

  int size_ = 0;
};

} // namespace NSQt
} // namespace NSApplication

#endif // NSAPPLICATION_NSQT_CSESSIONSTATISTICSMODEL_H
