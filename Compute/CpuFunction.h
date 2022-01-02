#ifndef NSAPPLICATION_NSCOMPUTE_CMATHFUNCTION_H
#define NSAPPLICATION_NSCOMPUTE_CMATHFUNCTION_H

#include "Functions.h"
#include "InstructionLevels.h"
#include "Library/FunctionModuleBase.h"

#include <vector>

#define MAX_VECTOR_SIZE 512
#include "3dparty/vectorclass/vectorclass.h"
#include "3dparty/vectorclass/vectormath_exp.h"

namespace NSApplication {
namespace NSCompute {

namespace NSMathFunctionDetail {
class CFunctionBase
    : public NSLibrary::FunctionModuleBase<
          double(const std::vector<double>&, const double), CInstrLevel::AVX> {
  using CBase = NSLibrary::FunctionModuleBase<
      double(const std::vector<double>&, const double), CInstrLevel::AVX>;
  using CBase::CBase;

protected:
  using CFunctions = NSCompute::CFunctions;

  struct CSse2Parameters {
    using CVect = Vec2d;
    static constexpr const size_t size = 2;
  };

  struct CAvxParameters {
    using CVect = Vec4d;
    static constexpr const size_t size = 4;
  };

  template<class TParameters, class TFunction>
  static double compute(const std::vector<double>& means, double arg) {
    if (means.empty())
      return 0.;
    using CVect = typename TParameters::CVect;
    using CFunction = TFunction;
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
  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CNormalApproximation1 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CNormalApproximation1();
  CNormalApproximation1(int instruction_level);

private:
  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CNormalApproximation2 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CNormalApproximation2();
  CNormalApproximation2(int instruction_level);

private:
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
  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CRayleighApproximation0 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CRayleighApproximation0();
  CRayleighApproximation0(int instruction_level);

private:
  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

class CRayleighApproximation1 : public NSMathFunctionDetail::CFunctionBase {
  using CBase = NSMathFunctionDetail::CFunctionBase;

public:
  CRayleighApproximation1();
  CRayleighApproximation1(int instruction_level);

private:
  static double compute_SSE2(const std::vector<double>& means, double arg);
  static double compute_AVX(const std::vector<double>& means, double arg);
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CMATHFUNCTION_H
