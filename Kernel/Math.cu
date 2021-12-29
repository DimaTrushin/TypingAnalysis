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

  X_.resize(X.size());
  Y_.resize(X.size());
  S_.resize(Samples.size());

  thrust::copy(Samples.begin(), Samples.end(), S_.begin());
  thrust::copy(X.begin(), X.end(), X_.begin());
  thrust::transform(X_.begin(), X_.end(), Y_.begin(),
                    CCompute<CFunctions::CNormal<0>>(S_));
  thrust::copy(Y_.begin(), Y_.end(), D0Y0->begin());
  thrust::transform(X_.begin(), X_.end(), Y_.begin(),
                    CCompute<CFunctions::CNormal<1>>(S_));
  thrust::copy(Y_.begin(), Y_.end(), D1Y0->begin());
  thrust::transform(X_.begin(), X_.end(), Y_.begin(),
                    CCompute<CFunctions::CMaxwellBoltzmann<0>>(S_));
  thrust::copy(Y_.begin(), Y_.end(), D0Y1->begin());
  thrust::transform(X_.begin(), X_.end(), Y_.begin(),
                    CCompute<CFunctions::CMaxwellBoltzmann<1>>(S_));
  thrust::copy(Y_.begin(), Y_.end(), D1Y1->begin());
  thrust::transform(X_.begin(), X_.end(), Y_.begin(),
                    CCompute<CFunctions::CRayleigh<0>>(S_));
  thrust::copy(Y_.begin(), Y_.end(), D0Y2->begin());
  thrust::transform(X_.begin(), X_.end(), Y_.begin(),
                    CCompute<CFunctions::CRayleigh<1>>(S_));
  thrust::copy(Y_.begin(), Y_.end(), D1Y2->begin());
}
} // namespace NSKernel
} // namespace NSApplication
