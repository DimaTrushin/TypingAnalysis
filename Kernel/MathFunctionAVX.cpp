#include "MathFunction.h"

namespace NSApplication {
namespace NSKernel {

double CNormalApproximation0::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  return compute<CAvxParameters>(means, arg);
}

double CNormalApproximation1::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  return compute<CAvxParameters>(means, arg);
}

double CNormalApproximation2::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  return compute<CAvxParameters>(means, arg);
}

double
CMaxwellBoltzmannApproximation0::compute_AVX(const std::vector<double>& means,
                                             double arg) {
  return compute<CAvxParameters>(means, arg);
}

double
CMaxwellBoltzmannApproximation1::compute_AVX(const std::vector<double>& means,
                                             double arg) {
  return compute<CAvxParameters>(means, arg);
}

double CRayleighApproximation0::compute_AVX(const std::vector<double>& means,
                                            double arg) {
  return compute<CAvxParameters>(means, arg);
}

double CRayleighApproximation1::compute_AVX(const std::vector<double>& means,
                                            double arg) {
  return compute<CAvxParameters>(means, arg);
}

} // namespace NSKernel
} // namespace NSApplication
