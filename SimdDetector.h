#ifndef NSAPPLICATION_CSIMDDETECTOR_H
#define NSAPPLICATION_CSIMDDETECTOR_H

namespace NSApplication {

class CSimdDetector {
public:
  CSimdDetector();
  int level() const;

private:
  int InstructionLevel_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CSIMDDETECTOR_H
