#include "Math.h"

#include <thrust/transform.h>
#include <thrust/transform_reduce.h>

namespace NSApplication {
namespace NSKernel {

void CMath::fillPlotsGPU(const CVectorD& Samples, const CVectorD& X,
                         CVectorD* D0Y0, CVectorD* D1Y0, CVectorD* D0Y1,
                         CVectorD* D1Y1, CVectorD* D0Y2, CVectorD* D1Y2) {
  assert(D0Y0);
  assert(D0Y0->size() == X.size());
  assert(D1Y0);
  assert(D1Y0->size() == X.size());
  assert(D0Y1);
  assert(D0Y1->size() == X.size());
  assert(D1Y1);
  assert(D1Y1->size() == X.size());
  assert(D0Y2);
  assert(D0Y2->size() == X.size());
  assert(D1Y2);
  assert(D1Y2->size() == X.size());

  // TO DO
  // CUDA code

  X_.resize(X.size());
  Y_.resize(X.size());

  thrust::copy(X.begin(), X.end(), X_.begin());
  // Compute D0Y0 in Y_
  //  thrust::transform(X_.begin(), X_.end(), Y_.begin(),
  //                    ComputeNormal0(Samples))
  thrust::copy(Y_.begin(), Y_.end(), D0Y0->begin());
  // Compute D1Y0 in Y_
  thrust::copy(Y_.begin(), Y_.end(), D1Y0->begin());
  // Compute D0Y1 in Y_
  thrust::copy(Y_.begin(), Y_.end(), D0Y1->begin());
  // Compute D1Y1 in Y_
  thrust::copy(Y_.begin(), Y_.end(), D1Y1->begin());
  // Compute D0Y2 in Y_
  thrust::copy(Y_.begin(), Y_.end(), D0Y2->begin());
  // Compute D1Y2 in Y_
  thrust::copy(Y_.begin(), Y_.end(), D1Y2->begin());
}
} // namespace NSKernel
} // namespace NSApplication
