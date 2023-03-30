#ifndef NSAPPLICATION_NSCOMPUTE_CMATH_H
#define NSAPPLICATION_NSCOMPUTE_CMATH_H

#include "Functions.h"

#ifndef DISABLE_CUDA
#include "CudaGate.h"
#include <thrust/device_vector.h>
#endif

#include <vector>

namespace NSApplication {
namespace NSCompute {

class CParallelModule;

class CMath {
#ifndef DISABLE_CUDA
  using CDevVectorD = thrust::device_vector<double>;
#endif
  using CVectorD = std::vector<double>;

public:
  CMath(CParallelModule& Parallel);

  bool isGpuAvailable() const;

  void fillPlots(const CVectorD& Samples, const CVectorD& X, CVectorD* D0Y0,
                 CVectorD* D1Y0, CVectorD* D0Y1, CVectorD* D1Y1, CVectorD* D0Y2,
                 CVectorD* D1Y2);

private:
  void fillPlotsCPU(const CVectorD& Samples, const CVectorD& X, CVectorD* D0Y0,
                    CVectorD* D1Y0, CVectorD* D0Y1, CVectorD* D1Y1,
                    CVectorD* D0Y2, CVectorD* D1Y2);
  void fillNormalPlot0(const CVectorD& Samples, const CVectorD& X,
                       CVectorD* pY);
  void fillNormalPlot1(const CVectorD& Samples, const CVectorD& X,
                       CVectorD* pY);
  void fillMBPlot0(const CVectorD& Samples, const CVectorD& X, CVectorD* pY);
  void fillMBPlot1(const CVectorD& Samples, const CVectorD& X, CVectorD* pY);
  void fillRPlot0(const CVectorD& Samples, const CVectorD& X, CVectorD* pY);
  void fillRPlot1(const CVectorD& Samples, const CVectorD& X, CVectorD* pY);

#ifndef DISABLE_CUDA
  void fillPlotsGPU(const CVectorD& Samples, const CVectorD& X, CVectorD* D0Y0,
                    CVectorD* D1Y0, CVectorD* D0Y1, CVectorD* D1Y1,
                    CVectorD* D0Y2, CVectorD* D1Y2);
#endif

  CParallelModule& Parallel_;
#ifndef DISABLE_CUDA
  CCudaGate CudaGate_;
  CDevVectorD X_;
  CDevVectorD S_;
  CDevVectorD Y_;
#endif
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CMATH_H
