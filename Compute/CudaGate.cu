#include "CudaGate.h"

#include <thrust/device_vector.h>
#include <thrust/transform.h>

namespace NSApplication {
namespace NSCompute {
namespace NSCudaGateDetail {

namespace {

class CCompute {
public:
  __device__ double operator()(double arg) const {
    return arg * arg;
  }
};

} // namespace

void CCudaGateImpl::setCudaContext() {
  // TO DO
  // Need to implement a proper method to initialize Cuda Context.
  // Probably need to use the driver api.
  thrust::device_vector<double> X(100);
  thrust::device_vector<double> Y(100);
  thrust::transform(X.begin(), X.end(), Y.begin(), CCompute());
}

} // namespace NSCudaGateDetail
} // namespace NSCompute
} // namespace NSApplication
