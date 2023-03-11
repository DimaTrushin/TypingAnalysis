#ifndef NSAPPLICATION_NSCOMPUTE_CPUFUNCTIONNOSIMD_H
#define NSAPPLICATION_NSCOMPUTE_CPUFUNCTIONNOSIMD_H

#include "Functions.h"

#include <vector>

namespace NSApplication {
namespace NSCompute {

namespace NSMathFunctionDetail {

class CFunctionBase {
public:
  template<class TFunction>
  static double compute(const std::vector<double>& means, double arg) {
    if (means.empty())
      return 0.;
    using CFunction = TFunction;
    double result = 0.;
    for (double mean : means) {
      result += CFunction::compute(mean, arg);
    }
    return result / static_cast<double>(means.size());
  }
};
} // namespace NSMathFunctionDetail

template<std::int64_t derivative, class = std::enable_if_t<(derivative < 3)>>
class CNormalApproximation : private NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  double operator()(const std::vector<double>& means, double arg) const {
    return CBase::compute<CFunctions::CNormal<derivative>>(means, arg);
  }
};

template<std::int64_t derivative, class = std::enable_if_t<(derivative < 2)>>
class CMaxwellBoltzmannApproximation
    : private NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  double operator()(const std::vector<double>& means, double arg) const {
    return CBase::compute<CFunctions::CMaxwellBoltzmann<derivative>>(means,
                                                                     arg);
  }
};

template<std::int64_t derivative, class = std::enable_if_t<(derivative < 2)>>
class CRayleighApproximation : private NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  double operator()(const std::vector<double>& means, double arg) const {
    return CBase::compute<CFunctions::CRayleigh<derivative>>(means, arg);
  }
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CPUFUNCTIONNOSIMD_H
