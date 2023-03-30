#ifndef NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H
#define NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H

#include "Kernel/StatisticsDescription.h"
#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/Localizer.h"
#include "Qt/SessionStatisticsModel.h"

#include <QObject>

#include <memory>

QT_BEGIN_NAMESPACE
class QTableView;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSStatisticsViewDetail {

class CStatisticsViewImpl : public NSQt::CSessionStatisticsModel {
  Q_OBJECT
  using CSessionStatisticsModel = NSQt::CSessionStatisticsModel;

  using CTextData = NSKernel::CTextData;
  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CDescription = NSKernel::CDescription;
  using CStatisticsDescription = NSKernel::CStatisticsDescription;
  using CStatisticsObserver = NSLibrary::CObserver<CStatisticsDescription>;
  using CStatisticsInput = NSLibrary::CHotInput<CStatisticsDescription>;

  using CLocalizer = NSLocal::CStatisticsViewLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

public:
  CStatisticsViewImpl(QTableView* TableView);
  CLocalizerObserver* localizerInput();
  CStatisticsObserver* statisticsDescriptionInput();

private:
  void handleStatistics(const CStatisticsDescription& Statistics);
  void setViewLocale(const CLocalizer& Localizer);

  int size() const override;
  const CDescription& data_(int row) const override;

  QTableView* TableView_;
  CLocalizerInput ViewLocalizerInput_;
  CStatisticsInput StatisticsInput_;
};
} // namespace NSStatisticsViewDetail

using CStatisticsView =
    NSLibrary::CViewWrapper<NSStatisticsViewDetail::CStatisticsViewImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H
