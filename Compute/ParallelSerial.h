#ifndef NSAPPLICATION_NSCOMPUTE_CPARALLELSERIAL_H
#define NSAPPLICATION_NSCOMPUTE_CPARALLELSERIAL_H

namespace NSApplication {
namespace NSCompute {

class CParallelSerial {
public:
  template<class TIndex, class TFunction>
  void for_(TIndex begin, TIndex end, const TFunction& F) {
    for (TIndex index = begin; index != end; ++index)
      F(index);
  }
};

} // namespace NSCompute
} // namespace NSApplication

#endif // NSAPPLICATION_NSCOMPUTE_CPARALLELSERIAL_H
