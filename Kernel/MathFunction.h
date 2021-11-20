#ifndef NSAPPLICATION_NSKERNEL_CMATHFUNCTION_H
#define NSAPPLICATION_NSKERNEL_CMATHFUNCTION_H

#include "InstructionLevels.h"
#include "Library/FunctionModuleBase.h"

#include <vector>

#define MAX_VECTOR_SIZE 512
#include "3dparty/vectorclass/vectorclass.h"
#include "3dparty/vectorclass/vectormath_exp.h"

namespace NSApplication {
namespace NSKernel {

namespace NSMathFunctionDetail {
class CFunctionBase
    : public NSLibrary::FunctionModuleBase<
          double(const std::vector<double>&, const double), CInstrLevel::AVX> {
  using CBase = NSLibrary::FunctionModuleBase<
      double(const std::vector<double>&, const double), CInstrLevel::AVX>;
  using CBase::CBase;

protected:
  struct CSse2Parameters {
    using CVect = Vec2d;
    static constexpr const size_t size = 2;
  };

  struct CAvxParameters {
    using CVect = Vec4d;
    static constexpr const size_t size = 4;
  };

  static constexpr const double one_over_sqrt_two_pi =
      0.398942280401432702863218082712;

  static constexpr const double four_over_sqrt_pi =
      2.2567583341910251477923178062431;

  template<typename T>
  static T deviation(T mean) {
    // All constants here were chosen empirically
    //    return 1.25 * sqrt(mean + 1.);
    //    return 2.5 * sqrt(mean + 1.);
    //    return 2. / 3. * (mean + 1.);
    //    return 1. / 8. * (mean + 10.);
    return 1. / 10. * mean + 10.;
  }

  template<class TParameters, template<class> class TFunction>
  static double compute_(const std::vector<double>& means, double arg) {
    if (means.empty())
      return 0.;
    using CVect = typename TParameters::CVect;
    using CFunction = TFunction<CVect>;
    CVect tmp_result = 0;
    size_t regular_part =
        means.size() & static_cast<size_t>(-TParameters::size);
    int leftover = static_cast<int>(means.size() - regular_part);
    CVect means_block;
    const double* data = means.data();
    const double* const regular_data = data + regular_part;

    for (; data < regular_data; data += TParameters::size) {
      means_block.load(data);
      tmp_result += CFunction::compute(means_block, arg);
    }
    means_block.load_partial(leftover, data);
    tmp_result += CFunction::compute(means_block, arg).cutoff(leftover);

    return horizontal_add(tmp_result) / static_cast<double>(means.size());
  }
};
} // namespace NSMathFunctionDetail

class CNormalApproximation0 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CNormalApproximation0();
  CNormalApproximation0(int instruction_level);

private:
  using CBase::one_over_sqrt_two_pi;

  // MinGW dies here trying to call this function in debug mode
  // SIGSEGV segmentation fault
  // This happens only in AVX mode, probably an issue with compiler flags
  template<class T>
  struct CFunction {
    static T compute(T mean, double arg) {
      T deviation = CBase::deviation(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_div * one_over_sqrt_two_pi;
    }
  };

  template<class TParameters>
  static double compute(const std::vector<double>& means, double arg) {
    return CBase::compute_<TParameters, CFunction>(means, arg);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CNormalApproximation1 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CNormalApproximation1();
  CNormalApproximation1(int instruction_level);

private:
  template<class T>
  struct CFunction {
    static T compute(T mean, double arg) {
      T deviation = CBase::deviation(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return -exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                  one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             arg_minus_mean;
    }
  };
  template<class TParameters>
  static double compute(const std::vector<double>& means, double arg) {
    return CBase::compute_<TParameters, CFunction>(means, arg);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CNormalApproximation2 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CNormalApproximation2();
  CNormalApproximation2(int instruction_level);

private:
  template<class T>
  struct CFunction {
    static T compute(T mean, double arg) {
      T deviation = CBase::deviation(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             (1. -
              arg_minus_mean * arg_minus_mean * one_over_div * one_over_div);
    }
  };
  template<class TParameters>
  static double compute(const std::vector<double>& means, double arg) {
    return CBase::compute_<TParameters, CFunction>(means, arg);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CMaxwellBoltzmannApproximation0
    : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CMaxwellBoltzmannApproximation0();
  CMaxwellBoltzmannApproximation0(int instruction_level);

private:
  using CBase::four_over_sqrt_pi;

  template<class T>
  struct CFunction {
    static T compute(T mean, double arg) {
      T arg_square = arg * arg;
      T mean_square = mean * mean;
      return four_over_sqrt_pi * arg_square * exp(-arg_square / mean_square) /
             (mean * mean_square);
    }
  };

  template<class TParameters>
  static double compute(const std::vector<double>& means, double arg) {
    return CBase::compute_<TParameters, CFunction>(means, arg);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CMaxwellBoltzmannApproximation1
    : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CMaxwellBoltzmannApproximation1();
  CMaxwellBoltzmannApproximation1(int instruction_level);

private:
  using CBase::four_over_sqrt_pi;

  template<class T>
  struct CFunction {
    static T compute(T mean, double arg) {
      T arg_square = arg * arg;
      T mean_square = mean * mean;
      return four_over_sqrt_pi * 2. * arg * (1 - arg_square / mean_square) *
             exp(-arg_square / mean_square) / (mean * mean_square);
    }
  };

  template<class TParameters>
  static double compute(const std::vector<double>& means, double arg) {
    return CBase::compute_<TParameters, CFunction>(means, arg);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CRayleighApproximation0 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CRayleighApproximation0();
  CRayleighApproximation0(int instruction_level);

private:
  template<class T>
  struct CFunction {
    static T compute(T mean, double arg) {
      return arg * exp(-arg * arg / (2. * mean * mean)) / (mean * mean);
    }
  };

  template<class TParameters>
  static double compute(const std::vector<double>& means, double arg) {
    return CBase::compute_<TParameters, CFunction>(means, arg);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CRayleighApproximation1 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CRayleighApproximation1();
  CRayleighApproximation1(int instruction_level);

private:
  template<class T>
  struct CFunction {
    static T compute(T mean, double arg) {
      T mean_square = mean * mean;
      T arg_square = arg * arg;
      return (1. - arg_square / mean_square) *
             exp(-arg_square / (2. * mean_square)) / mean_square;
    }
  };

  template<class TParameters>
  static double compute(const std::vector<double>& means, double arg) {
    return CBase::compute_<TParameters, CFunction>(means, arg);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMATHFUNCTION_H
