#include "CudaGate.h"

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
  // This initialization code does not work if X_ and Y_ are local
  // to the function. Thus, I have to make them members of the class.
  X_.resize(100);
  Y_.resize(100);
  thrust::transform(X_.begin(), X_.end(), Y_.begin(), CCompute());
  X_.clear();
  Y_.clear();
}

} // namespace NSCudaGateDetail
} // namespace NSCompute
} // namespace NSApplication
