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

class CStatisticsViewImpl : public NSQt::CSessionStatisticsModel {
  Q_OBJECT
  using CSessionStatisticsModel = NSQt::CSessionStatisticsModel;

  using CTextData = NSKernel::CTextData;
  using CTextDataObserver = NSLibrary::CObserver<CTextData>;
  using CTextDataInput = NSLibrary::CHotInput<CTextData>;

  using CDescription = CSessionStatisticsModel::CDescription;
  using CStatisticsDescription =
      CSessionStatisticsModel::CStatisticsDescription;

  using CViewLocalizer = NSLocal::CStatisticsViewLocalizer;
  using CViewLocalizerObserver = NSLibrary::CObserver<CViewLocalizer>;
  using CViewLocalizerInput = NSLibrary::CHotInput<CViewLocalizer>;

  using CStatisticsLocalizer = NSLocal::CStatisticsLocalizer;
  using CStatisticsLocalizerObserver =
      NSLibrary::CObserver<CStatisticsLocalizer>;
  using CStatisticsLocalizerInput = NSLibrary::CHotInput<CStatisticsLocalizer>;

public:
  CStatisticsViewImpl(QTableView* TableView);
  CTextDataObserver* textDataInput();
  CViewLocalizerObserver* viewLocalizerInput();
  CStatisticsLocalizerObserver* statisticsLocalizerInput();

private:
  void handleTextData(const CTextData& Data);

  CStatisticsDescription createStatisticsData(const CTextData& Data);

  void setViewLocale(const CViewLocalizer& Localizer);
  void setStatisticsLocale(const CStatisticsLocalizer& Localizer);

  QString fullTextLength() const;
  QString printedTextLength() const;
  QString deletedSymbols() const;
  QString mistakePlaces() const;
  QString mistakes() const;
  QString mistakesPercent() const;
  QString fullTextDuration() const;
  QString printedTextDuration() const;
  QString fullTextSpeed() const;
  QString printedTextSpeed() const;

  QTableView* TableView_;
  CTextDataInput TextDataInput_;
  CViewLocalizerInput ViewLocalizerInput_;
  CStatisticsLocalizerInput StatisticsLocalizerInput_;
};
} // namespace NSStatisticsViewDetail

using CStatisticsView =
    NSLibrary::CViewWrapper<NSStatisticsViewDetail::CStatisticsViewImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSTATISTICSVIEW_H
