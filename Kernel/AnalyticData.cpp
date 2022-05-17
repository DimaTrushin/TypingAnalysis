#include "AnalyticData.h"

namespace NSApplication {
namespace NSKernel {

const CTextData& CAnalyticData::textData() const {
  return TextData;
}

const CPlotData& CAnalyticData::plotData() const {
  return PlotData;
}

} // namespace NSKernel
} // namespace NSApplication
