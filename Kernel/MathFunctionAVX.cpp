#define MAX_VECTOR_SIZE 512
#include "3dparty/vectorclass/vectorclass.h"
#include "3dparty/vectorclass/vectormath_exp.h"

// This include must be the last one
// because it contains function templates that must see vector class includes
#include "MathFunction.h"

namespace NSApplication {
namespace NSKernel {

double CNormalApproximation0::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  Vec4d tmp_result = 0;
  size_t regular_part = means.size() & static_cast<size_t>(-4);
  int leftover = static_cast<int>(means.size() - regular_part);
  Vec4d means_block;
  const double* data = means.data();
  const double* const regular_data = data + regular_part;

  for (; data < regular_data; data += 4) {
    means_block.load(data);
    tmp_result += function0(means_block, arg);
  }
  means_block.load_partial(leftover, data);
  tmp_result += function0(means_block, arg).cutoff(leftover);

  return horizontal_add(tmp_result) / static_cast<double>(means.size());
}

double CNormalApproximation1::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  Vec4d tmp_result = 0;
  size_t regular_part = means.size() & static_cast<size_t>(-4);
  int leftover = static_cast<int>(means.size() - regular_part);
  Vec4d means_block;
  const double* data = means.data();
  const double* const regular_data = data + regular_part;

  for (; data < regular_data; data += 4) {
    means_block.load(data);
    tmp_result += function1(means_block, arg);
  }
  means_block.load_partial(leftover, data);
  tmp_result += function1(means_block, arg).cutoff(leftover);

  return horizontal_add(tmp_result) / static_cast<double>(means.size());
}

double CNormalApproximation2::compute_AVX(const std::vector<double>& means,
                                          double arg) {
  Vec4d tmp_result = 0;
  size_t regular_part = means.size() & static_cast<size_t>(-4);
  int leftover = static_cast<int>(means.size() - regular_part);
  Vec4d means_block;
  const double* data = means.data();
  const double* const regular_data = data + regular_part;

  for (; data < regular_data; data += 4) {
    means_block.load(data);
    tmp_result += function2(means_block, arg);
  }
  means_block.load_partial(leftover, data);
  tmp_result += function2(means_block, arg).cutoff(leftover);

  return horizontal_add(tmp_result) / static_cast<double>(means.size());
}

} // namespace NSKernel
} // namespace NSApplication
