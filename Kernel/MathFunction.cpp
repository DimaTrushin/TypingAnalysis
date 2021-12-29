#include "MathFunction.h"

#include "SimdDetectorAccess.h"

namespace NSApplication {
namespace NSKernel {

CNormalApproximation0::CNormalApproximation0()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

CNormalApproximation0::CNormalApproximation0(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CNormalApproximation0::compute_SSE2(const std::vector<double>& means,
                                           double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CNormal<0>>(means, arg);
}

CNormalApproximation1::CNormalApproximation1()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

CNormalApproximation1::CNormalApproximation1(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CNormalApproximation1::compute_SSE2(const std::vector<double>& means,
                                           double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CNormal<1>>(means, arg);
}

CNormalApproximation2::CNormalApproximation2()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

CNormalApproximation2::CNormalApproximation2(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CNormalApproximation2::compute_SSE2(const std::vector<double>& means,
                                           double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CNormal<2>>(means, arg);
}

CMaxwellBoltzmannApproximation0::CMaxwellBoltzmannApproximation0()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

CMaxwellBoltzmannApproximation0::CMaxwellBoltzmannApproximation0(
    int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double
CMaxwellBoltzmannApproximation0::compute_SSE2(const std::vector<double>& means,
                                              double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CMaxwellBoltzmann<0>>(
      means, arg);
}

CMaxwellBoltzmannApproximation1::CMaxwellBoltzmannApproximation1()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

CMaxwellBoltzmannApproximation1::CMaxwellBoltzmannApproximation1(
    int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double
CMaxwellBoltzmannApproximation1::compute_SSE2(const std::vector<double>& means,
                                              double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CMaxwellBoltzmann<1>>(
      means, arg);
}

CRayleighApproximation0::CRayleighApproximation0()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

CRayleighApproximation0::CRayleighApproximation0(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CRayleighApproximation0::compute_SSE2(const std::vector<double>& means,
                                             double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CRayleigh<0>>(means, arg);
}

CRayleighApproximation1::CRayleighApproximation1()
    : CBase(&compute_AVX, &compute_SSE2, CSimdDetectorAccess()->level()) {
}

CRayleighApproximation1::CRayleighApproximation1(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CRayleighApproximation1::compute_SSE2(const std::vector<double>& means,
                                             double arg) {
  return CBase::compute<CSse2Parameters, CFunctions::CRayleigh<1>>(means, arg);
}

} // namespace NSKernel
} // namespace NSApplication
