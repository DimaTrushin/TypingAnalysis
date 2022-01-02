#include "CpuFunction.h"

namespace NSApplication {
namespace NSCompute {

double CNormalApproximation0::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CNormal<0>>(means, arg);
}

double CNormalApproximation1::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CNormal<1>>(means, arg);
}

double CNormalApproximation2::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CNormal<2>>(means, arg);
}

double
CMaxwellBoltzmannApproximation0::compute_AVX(const std::vector<double>& means,
                                             double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CMaxwellBoltzmann<0>>(means,
                                                                          arg);
}

double
CMaxwellBoltzmannApproximation1::compute_AVX(const std::vector<double>& means,
                                             double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CMaxwellBoltzmann<1>>(means,
                                                                          arg);
}

double CRayleighApproximation0::compute_AVX(const std::vector<double>& means,
                                            double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CRayleigh<0>>(means, arg);
}

double CRayleighApproximation1::compute_AVX(const std::vector<double>& means,
                                            double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CRayleigh<1>>(means, arg);
}

} // namespace NSCompute
} // namespace NSApplication
