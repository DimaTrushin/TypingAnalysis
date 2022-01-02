#include "CpuFunction.h"

#include "SimdDetectorAccess.h"

namespace NSApplication {
namespace NSCompute {

template<>
double CNormalApproximation<0>::compute_SSE2(const std::vector<double>& means,
                                             double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CNormal<0>>(means, arg);
}

template<>
double CNormalApproximation<1>::compute_SSE2(const std::vector<double>& means,
                                             double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CNormal<1>>(means, arg);
}

template<>
double CNormalApproximation<2>::compute_SSE2(const std::vector<double>& means,
                                             double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CNormal<2>>(means, arg);
}

template<>
CNormalApproximation<0>::CNormalApproximation()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

template<>
CNormalApproximation<1>::CNormalApproximation()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

template<>
CNormalApproximation<2>::CNormalApproximation()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

template<>
CNormalApproximation<0>::CNormalApproximation(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

template<>
CNormalApproximation<1>::CNormalApproximation(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

template<>
CNormalApproximation<2>::CNormalApproximation(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

template<>
double CMaxwellBoltzmannApproximation<0>::compute_SSE2(
    const std::vector<double>& means, double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CMaxwellBoltzmann<0>>(
      means, arg);
}

template<>
double CMaxwellBoltzmannApproximation<1>::compute_SSE2(
    const std::vector<double>& means, double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CMaxwellBoltzmann<0>>(
      means, arg);
}

template<>
CMaxwellBoltzmannApproximation<0>::CMaxwellBoltzmannApproximation()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

template<>
CMaxwellBoltzmannApproximation<1>::CMaxwellBoltzmannApproximation()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

template<>
CMaxwellBoltzmannApproximation<0>::CMaxwellBoltzmannApproximation(
    int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

template<>
CMaxwellBoltzmannApproximation<1>::CMaxwellBoltzmannApproximation(
    int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

template<>
double CRayleighApproximation<0>::compute_SSE2(const std::vector<double>& means,
                                               double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CRayleigh<0>>(means, arg);
}

template<>
double CRayleighApproximation<1>::compute_SSE2(const std::vector<double>& means,
                                               double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CRayleigh<1>>(means, arg);
}

template<>
CRayleighApproximation<0>::CRayleighApproximation()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

template<>
CRayleighApproximation<1>::CRayleighApproximation()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

template<>
CRayleighApproximation<0>::CRayleighApproximation(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

template<>
CRayleighApproximation<1>::CRayleighApproximation(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

} // namespace NSCompute
} // namespace NSApplication
