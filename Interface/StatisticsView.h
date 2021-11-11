#ifndef NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H
#define NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H

#include <QObject>

#include <memory>

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Qt/SessionStatisticsModel.h"

QT_BEGIN_NAMESPACE
class QTableView;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSStatisticsViewDetail {

class CStatisticsViewImpl {
  using CSessionStatisticsModel = NSQt::CSessionStatisticsModel;

  using CTextData = NSKernel::CTextData;
  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CDescription = CSessionStatisticsModel::CDescription;
  using CStatisticsDescription =
      CSessionStatisticsModel::CStatisticsDescription;

public:
  CStatisticsViewImpl(QTableView* TableView);
  CTextDataObserver* textDataInput();

private:
  void handleTextData(const CTextData& Data);

  CStatisticsDescription createStatisticsData(const CTextData& Data);

  QTableView* TableView_;
  CSessionStatisticsModel StatisticsModel_;
  CTextDataInput TextDataInput_;
};
} // namespace NSStatisticsViewDetail

using CStatisticsView =
    NSLibrary::CViewWrapper<NSStatisticsViewDetail::CStatisticsViewImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H
