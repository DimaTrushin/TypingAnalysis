#ifndef NSAPPLICATION_NSKEYBOARD_CRAWINPUTREADER_H
#define NSAPPLICATION_NSKEYBOARD_CRAWINPUTREADER_H

#include <vector>
#include <Windows.h>


namespace NSApplication {
namespace NSKeyboard {


class CSafeRawBuffer {
  struct alignas(alignof(RAWINPUT)) CAlgnBlock {
    static constexpr unsigned int size = alignof(RAWINPUT);
    BYTE byte[size];
  };

public:
  const RAWINPUT* operator->() const;
  const RAWINPUT* getPRawInput() const;
  LPBYTE data();

  unsigned int size() const;
  void resize(unsigned int newSize);

  bool isKeyboard() const;
  const RAWKEYBOARD& getKeyboard() const;

private:
  std::vector<CAlgnBlock> Buffer_;
  unsigned int size_ = 0;
};


class CRawInputReader {
public:
  const RAWKEYBOARD& getKeyboardData(LPARAM lParam);

private:
  void adjustBuffer(LPARAM lParam);
  void readRawInputToBuffer(LPARAM lParam);
  static unsigned int getRawDataSize(LPARAM lParam);

  CSafeRawBuffer Buffer_;
};

} // NSKeyboard
} // NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CRAWINPUTREADER_H
