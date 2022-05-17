#ifndef NSAPPLICATION_NSKERNEL_CANALYTICDATA_H
#define NSAPPLICATION_NSKERNEL_CANALYTICDATA_H

#include "PlotData.h"
#include "TextData.h"

namespace NSApplication {
namespace NSKernel {

struct CAnalyticData {
  std::reference_wrapper<const CTextData> TextData;
  std::reference_wrapper<const CPlotData> PlotData;

  const CTextData& textData() const;
  const CPlotData& plotData() const;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CANALYTICDATA_H
