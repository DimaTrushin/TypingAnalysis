#include "RawInputReader.h"

#include <cassert>
#include <stdexcept>

namespace NSApplication {
namespace NSKeyboard {


const RAWINPUT* CSafeRawBuffer::operator->() const {
  return PRAWINPUT(Buffer_.data());
}

const RAWINPUT* CSafeRawBuffer::getPRawInput() const {
  return PRAWINPUT(Buffer_.data());
}

LPBYTE CSafeRawBuffer::data() {
  return &(Buffer_.data()->byte[0]);
}

unsigned int CSafeRawBuffer::size() const {
  return size_;
}

void CSafeRawBuffer::resize(unsigned int newSize) {
  unsigned int bufferSize = newSize / CAlgnBlock::size +
                            (newSize % CAlgnBlock::size ? 1 : 0);
  Buffer_.resize(bufferSize);
  size_ = newSize;
}

bool CSafeRawBuffer::isKeyboard() const {
  return getPRawInput()->header.dwType == RIM_TYPEKEYBOARD;
}

const RAWKEYBOARD& CSafeRawBuffer::getKeyboard() const {
  return getPRawInput()->data.keyboard;
}


const RAWKEYBOARD& CRawInputReader::getKeyboardData(LPARAM lParam) {
  adjustBuffer(lParam);
  readRawInputToBuffer(lParam);
  assert(Buffer_.isKeyboard());
  return Buffer_.getKeyboard();
}

void CRawInputReader::adjustBuffer(LPARAM lParam) {
  Buffer_.resize(getRawDataSize(lParam));
}

void CRawInputReader::readRawInputToBuffer(LPARAM lParam) {
  unsigned int bufferSize = Buffer_.size();
  if (::GetRawInputData(HRAWINPUT(lParam),
                        RID_INPUT,
                        Buffer_.data(),
                        &bufferSize,
                        sizeof(RAWINPUTHEADER)) != bufferSize)
    throw std::runtime_error("GetRawInputData does not return correct size !\n");
}

unsigned int CRawInputReader::getRawDataSize(LPARAM lParam) {
  unsigned int dwSize;
  ::GetRawInputData(HRAWINPUT(lParam),
                    RID_INPUT,
                    nullptr,
                    &dwSize,
                    sizeof(RAWINPUTHEADER));
  return dwSize;
}

} // NSKeyboard
} // NSApplication
