#ifndef NSAPPLICATION_NSKERNEL_CMATH_H
#define NSAPPLICATION_NSKERNEL_CMATH_H

#include "../Compute/CudaGate.h"
#include "../Compute/Functions.h"
#include <thrust/device_vector.h>
#include <vector>

namespace NSApplication {
namespace NSKernel {

// TO DO
// Move to NSCompute
// This object depends on Parallel module, need to make this dependence explicit
class CMath {
  using CDevVectorD = thrust::device_vector<double>;
  using CVectorD = std::vector<double>;
  using CCudaGate = NSCompute::CCudaGate;
  using CFunctions = NSCompute::CFunctions;

public:
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

  void fillPlotsGPU(const CVectorD& Samples, const CVectorD& X, CVectorD* D0Y0,
                    CVectorD* D1Y0, CVectorD* D0Y1, CVectorD* D1Y1,
                    CVectorD* D0Y2, CVectorD* D1Y2);

  CCudaGate CudaGate_;
  CDevVectorD X_;
  CDevVectorD S_;
  CDevVectorD Y_;
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMATH_H