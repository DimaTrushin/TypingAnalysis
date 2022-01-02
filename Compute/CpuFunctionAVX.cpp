#include "CpuFunction.h"

namespace NSApplication {
namespace NSCompute {

template<>
double CNormalApproximation<0>::compute_AVX(const std::vector<double>& means,
                                            double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CNormal<0>>(means, arg);
}

template<>
double CNormalApproximation<1>::compute_AVX(const std::vector<double>& means,
                                            double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CNormal<1>>(means, arg);
}

template<>
double CNormalApproximation<2>::compute_AVX(const std::vector<double>& means,
                                            double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CNormal<2>>(means, arg);
}

template<>
double
CMaxwellBoltzmannApproximation<0>::compute_AVX(const std::vector<double>& means,
                                               double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CMaxwellBoltzmann<0>>(means,
                                                                          arg);
}

template<>
double
CMaxwellBoltzmannApproximation<1>::compute_AVX(const std::vector<double>& means,
                                               double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CMaxwellBoltzmann<1>>(means,
                                                                          arg);
}

template<>
double CRayleighApproximation<0>::compute_AVX(const std::vector<double>& means,
                                              double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CRayleigh<0>>(means, arg);
}

template<>
double CRayleighApproximation<1>::compute_AVX(const std::vector<double>& means,
                                              double arg) {
  return CBase::compute<CAvxParameters, CFunctions::CRayleigh<1>>(means, arg);
}

} // namespace NSCompute
} // namespace NSApplication
