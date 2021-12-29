#include "Math.h"

#include "Kernel/MathFunction.h"
#include "ParallelModuleAccess.h"

namespace NSApplication {
namespace NSKernel {

bool CMath::isGpuAvailable() const {
  // TO DO
  return false;
}

void CMath::fillPlots(const CVectorD& Samples, const CVectorD& X,
                      CVectorD* D0Y0, CVectorD* D1Y0, CVectorD* D0Y1,
                      CVectorD* D1Y1, CVectorD* D0Y2, CVectorD* D1Y2) {
  if (isGpuAvailable())
    fillPlotsGPU(Samples, X, D0Y0, D1Y0, D0Y1, D1Y1, D0Y2, D1Y2);
  else
    fillPlotsCPU(Samples, X, D0Y0, D1Y0, D0Y1, D1Y1, D0Y2, D1Y2);
}

void CMath::fillPlotsCPU(const CVectorD& Samples, const CVectorD& X,
                         CVectorD* D0Y0, CVectorD* D1Y0, CVectorD* D0Y1,
                         CVectorD* D1Y1, CVectorD* D0Y2, CVectorD* D1Y2) {
  fillNormalPlot0(Samples, X, D0Y0);
  fillNormalPlot1(Samples, X, D1Y0);
  fillMBPlot0(Samples, X, D0Y1);
  fillMBPlot1(Samples, X, D1Y1);
  fillRPlot0(Samples, X, D0Y2);
  fillRPlot1(Samples, X, D1Y2);
}

void CMath::fillNormalPlot0(const CVectorD& Samples, const CVectorD& X,
                            CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CNormalApproximation0 Function;
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillNormalPlot1(const CVectorD& Samples, const CVectorD& X,
                            CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CNormalApproximation1 Function;
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillMBPlot0(const CVectorD& Samples, const CVectorD& X,
                        CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CMaxwellBoltzmannApproximation0 Function;
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillMBPlot1(const CVectorD& Samples, const CVectorD& X,
                        CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CMaxwellBoltzmannApproximation1 Function;
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillRPlot0(const CVectorD& Samples, const CVectorD& X,
                       CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CRayleighApproximation0 Function;
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillRPlot1(const CVectorD& Samples, const CVectorD& X,
                       CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CRayleighApproximation1 Function;
  CParallelAccess Parallel;
  Parallel->for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillPlotsGPU(const CVectorD& Samples, const CVectorD& X,
                         CVectorD* D0Y0, CVectorD* D1Y0, CVectorD* D0Y1,
                         CVectorD* D1Y1, CVectorD* D0Y2, CVectorD* D1Y2) {
}

} // namespace NSKernel
} // namespace NSApplication
