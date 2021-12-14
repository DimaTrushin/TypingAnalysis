#ifndef NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H
#define NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H

#include <QObject>

#include <memory>

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/Localizer.h"
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

  using CLocalizer = NSLocal::CStatisticsViewLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

public:
  CStatisticsViewImpl(QTableView* TableView);
  CTextDataObserver* textDataInput();
  CLocalizerObserver* localizerInput();

private:
  void handleTextData(const CTextData& Data);

  CStatisticsDescription createStatisticsData(const CTextData& Data);

  void setLocale(const CLocalizer& Localizer);

  QTableView* TableView_;
  CSessionStatisticsModel StatisticsModel_;
  CTextDataInput TextDataInput_;
  CLocalizerInput LocalizerInput_;
};
} // namespace NSStatisticsViewDetail

using CStatisticsView =
    NSLibrary::CViewWrapper<NSStatisticsViewDetail::CStatisticsViewImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H
