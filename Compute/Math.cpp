#ifdef _MSC_VER
#pragma warning(disable : 4324)
#pragma warning(disable : 4515)
#endif
#include "Math.h"
#ifdef _MSC_VER
#pragma warning(default : 4324)
#pragma warning(default : 4515)
#endif

#ifndef DISABLE_SIMD
#include "CpuFunction.h"
#else
#include "CpuFunctionNoSimd.h"
#endif
#include "ParallelModule.h"

namespace NSApplication {
namespace NSCompute {

CMath::CMath(CParallelModule& Parallel) : Parallel_(Parallel) {
}

bool CMath::isGpuAvailable() const {
#ifndef DISABLE_CUDA
  return CudaGate_.isAvailable();
#else
  return false;
#endif
}

void CMath::fillPlots(const CVectorD& Samples, const CVectorD& X,
                      CVectorD* D0Y0, CVectorD* D1Y0, CVectorD* D0Y1,
                      CVectorD* D1Y1, CVectorD* D0Y2, CVectorD* D1Y2) {
#ifndef DISABLE_CUDA
  if (isGpuAvailable())
    fillPlotsGPU(Samples, X, D0Y0, D1Y0, D0Y1, D1Y1, D0Y2, D1Y2);
  else
#endif
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
  CNormalApproximation<0> Function;
  Parallel_.for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillNormalPlot1(const CVectorD& Samples, const CVectorD& X,
                            CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CNormalApproximation<1> Function;
  Parallel_.for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillMBPlot0(const CVectorD& Samples, const CVectorD& X,
                        CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CMaxwellBoltzmannApproximation<0> Function;
  Parallel_.for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillMBPlot1(const CVectorD& Samples, const CVectorD& X,
                        CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CMaxwellBoltzmannApproximation<1> Function;
  Parallel_.for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillRPlot0(const CVectorD& Samples, const CVectorD& X,
                       CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CRayleighApproximation<0> Function;
  Parallel_.for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

void CMath::fillRPlot1(const CVectorD& Samples, const CVectorD& X,
                       CVectorD* pY) {
  assert(pY);
  assert(pY->size() == X.size());
  CVectorD& Y = *pY;
  CRayleighApproximation<1> Function;
  Parallel_.for_(size_t(0), X.size(), [&](size_t i) {
    Y[i] = Function(Samples, X[i]);
    ;
  });
}

} // namespace NSCompute
} // namespace NSApplication
