#define MAX_VECTOR_SIZE 512
#include "3dparty/vectorclass/vectorclass.h"
#include "3dparty/vectorclass/vectormath_exp.h"

// This include must be the last one
// because it contains function templates that must see vector class includes
#include "MathFunction.h"

namespace NSApplication {
namespace NSKernel {

CDensity0::CDensity0(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CDensity0::compute_SSE2(const std::vector<double>& means, double arg) {
  Vec2d tmp_result = 0;
  size_t regular_part = means.size() & static_cast<size_t>(-2);
  int leftover = static_cast<int>(means.size() - regular_part);
  Vec2d means_block;
  const double* data = means.data();
  const double* const regular_data = data + regular_part;

  for (; data < regular_data; data += 2) {
    means_block.load(data);
    tmp_result += function0(means_block, arg);
  }
  means_block.load_partial(leftover, data);
  tmp_result += function0(means_block, arg).cutoff(leftover);

  return horizontal_add(tmp_result) / static_cast<double>(means.size());
}

CDensity1::CDensity1(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CDensity1::compute_SSE2(const std::vector<double>& means, double arg) {
  Vec2d tmp_result = 0;
  size_t regular_part = means.size() & static_cast<size_t>(-2);
  int leftover = static_cast<int>(means.size() - regular_part);
  Vec2d means_block;
  const double* data = means.data();
  const double* const regular_data = data + regular_part;

  for (; data < regular_data; data += 2) {
    means_block.load(data);
    tmp_result += function1(means_block, arg);
  }
  means_block.load_partial(leftover, data);
  tmp_result += function1(means_block, arg).cutoff(leftover);

  return horizontal_add(tmp_result) / static_cast<double>(means.size());
}

CDensity2::CDensity2(int instruction_level)
    : CBase(&compute_AVX, &compute_SSE2, instruction_level) {
}

double CDensity2::compute_SSE2(const std::vector<double>& means, double arg) {
  Vec2d tmp_result = 0;
  size_t regular_part = means.size() & static_cast<size_t>(-2);
  int leftover = static_cast<int>(means.size() - regular_part);
  Vec2d means_block;
  const double* data = means.data();
  const double* const regular_data = data + regular_part;

  for (; data < regular_data; data += 2) {
    means_block.load(data);
    tmp_result += function2(means_block, arg);
  }
  means_block.load_partial(leftover, data);
  tmp_result += function2(means_block, arg).cutoff(leftover);

  return horizontal_add(tmp_result) / static_cast<double>(means.size());
}

} // namespace NSKernel
} // namespace NSApplication
