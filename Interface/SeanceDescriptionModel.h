#ifndef NSAPPLICATION_NSINTERFACE_CSEANCEDESCRIPTIONMODEL_H
#define NSAPPLICATION_NSINTERFACE_CSEANCEDESCRIPTIONMODEL_H

#include <QAbstractItemModel>
#include <QItemSelection>
#include <deque>

namespace NSApplication {
namespace NSKernel {
class CSeance;
class CSession;
} // namespace NSKernel

namespace NSInterface {

class CSeanceDescriptionModel : public QAbstractItemModel {
  Q_OBJECT
  using CSeance = NSKernel::CSeance;
  using CSession = NSKernel::CSession;

public:
  struct CDescription {
    QString Text;
    size_t Size;
  };

  QModelIndex index(int row, int column,
                    const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& child) const override;
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  bool appendFromSeance(const CSeance&);
  bool clear();

signals:
  void selectionChanged(int level, int index);

public slots:
  void onSelectionChanged(const QItemSelection& selected,
                          const QItemSelection& deselected);

private:
  int get_level(const QModelIndex&) const;
  void* make_level(int level) const;
  int size() const;

  QVariant get_regular_data(int row, int column) const;

  QString currentSeanceName() const;
  QString headerName(int column) const;

  QString getSessionDescription(const CSession&) const;

  static constexpr const char kDefaultSeanceName_[] = "Current Seance";
  static constexpr const char kDefaultSessionDescription_[] = "Description";
  static constexpr const char kDefaultSizeDescription_[] = "Size";

  std::deque<CDescription> Data_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSEANCEDESCRIPTIONMODEL_H
