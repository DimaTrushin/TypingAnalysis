#ifndef NSAPPLICATION_NSKERNEL_CMATHFUNCTION_H
#define NSAPPLICATION_NSKERNEL_CMATHFUNCTION_H

#include "InstructionLevels.h"
#include "Library/FunctionModuleBase.h"

#include <vector>

namespace NSApplication {
namespace NSKernel {

namespace NSMathFunctionDetail {
class CFunctionBase
    : public NSLibrary::FunctionModuleBase<
          double(const std::vector<double>&, const double), CInstrLevel::AVX> {
  using CBase = NSLibrary::FunctionModuleBase<
      double(const std::vector<double>&, const double), CInstrLevel::AVX>;

public:
  using CBase::CBase;
  static constexpr const double one_over_sqrt_two_pi =
      0.398942280401432702863218082712;
  template<typename T>
  static T deviation(T mean) {
    return 1.25 * sqrt(mean + 1.);
  }
};
} // namespace NSMathFunctionDetail

class CDensity0 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CDensity0();
  CDensity0(int instruction_level);

private:
  using CBase::one_over_sqrt_two_pi;

  // MinGW dies here trying to call this function in debug mode
  // SIGSEGV segmentation fault
  // This happens only in AVX mode, probably an issue with compiler flags
  template<typename T>
  static T function0(T mean, double arg) {
    T deviation = CBase::deviation(mean);
    T one_over_div = 1. / deviation;
    T arg_minus_mean = arg - mean;

    return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
               one_over_div) *
           one_over_div * one_over_sqrt_two_pi;
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CDensity1 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CDensity1();
  CDensity1(int instruction_level);

private:
  template<typename T>
  static T function1(T mean, double arg) {
    T deviation = CBase::deviation(mean);
    T one_over_div = 1. / deviation;
    T arg_minus_mean = arg - mean;

    return -exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                one_over_div) *
           one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
           arg_minus_mean;
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CDensity2 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CDensity2();
  CDensity2(int instruction_level);

private:
  template<typename T>
  static T function2(T mean, double arg) {
    T deviation = CBase::deviation(mean);
    T one_over_div = 1. / deviation;
    T arg_minus_mean = arg - mean;

    return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
               one_over_div) *
           one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
           (1. - arg_minus_mean * arg_minus_mean * one_over_div * one_over_div);
  }

  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};
} // namespace NSKernel
} // namespace NSApplication

#endif // NSAPPLICATION_NSKERNEL_CMATHFUNCTION_H
