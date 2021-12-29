#ifndef NSAPPLICATION_NSCOMPUTE_CFUNCTIONS_H
#define NSAPPLICATION_NSCOMPUTE_CFUNCTIONS_H

#include <cstdint>

namespace NSApplication {
namespace NSCompute {

class CFunctions {

  static constexpr const double one_over_sqrt_two_pi =
      0.398942280401432702863218082712;

  static constexpr const double four_over_sqrt_pi =
      2.2567583341910251477923178062431;

  template<typename T>
  static T deviation(T mean) {
    // All constants here were chosen empirically
    return 1. / 10. * mean + 10.;
  }

public:
  template<int64_t derivative>
  struct CNormal;

  template<>
  struct CNormal<0> {

    // MinGW dies here trying to call this function in debug mode
    // SIGSEGV segmentation fault
    // This happens only in AVX mode, probably an issue with compiler flags
    template<class T>
    static T compute(T mean, double arg) {
      T Deviation = deviation(mean);
      T one_over_div = 1. / Deviation;
      T arg_minus_mean = arg - mean;

      return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_div * one_over_sqrt_two_pi;
    }
  };
  template<>
  struct CNormal<1> {
    template<class T>
    static T compute(T mean, double arg) {
      T Deviation = deviation(mean);
      T one_over_div = 1. / Deviation;
      T arg_minus_mean = arg - mean;

      return -exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                  one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             arg_minus_mean;
    }
  };

  template<>
  struct CNormal<2> {
    template<class T>
    static T compute(T mean, double arg) {
      T Deviation = deviation(mean);
      T one_over_div = 1. / Deviation;
      T arg_minus_mean = arg - mean;

      return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             (1. -
              arg_minus_mean * arg_minus_mean * one_over_div * one_over_div);
    }
  };

  template<int64_t derivative>
  struct CMaxwellBoltzmann;

  template<>
  struct CMaxwellBoltzmann<0> {
    template<class T>
    static T compute(T mean, double arg) {
      T arg_square = arg * arg;
      T mean_square = mean * mean;
      return four_over_sqrt_pi * arg_square * exp(-arg_square / mean_square) /
             (mean * mean_square);
    }
  };
  template<>
  struct CMaxwellBoltzmann<1> {
    template<class T>
    static T compute(T mean, double arg) {
      T arg_square = arg * arg;
      T mean_square = mean * mean;
      return four_over_sqrt_pi * 2. * arg * (1 - arg_square / mean_square) *
             exp(-arg_square / mean_square) / (mean * mean_square);
    }
  };

  template<int64_t derivative>
  struct CRayleigh;

  template<>
  struct CRayleigh<0> {
    template<class T>
    static T compute(T mean, double arg) {
      return arg * exp(-arg * arg / (2. * mean * mean)) / (mean * mean);
    }
  };
  template<>
  struct CRayleigh<1> {
    template<class T>
    static T compute(T mean, double arg) {
      T mean_square = mean * mean;
      T arg_square = arg * arg;
      return (1. - arg_square / mean_square) *
             exp(-arg_square / (2. * mean_square)) / mean_square;
    }
  };
}; // namespace NSCompute

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CFUNCTIONS_H
