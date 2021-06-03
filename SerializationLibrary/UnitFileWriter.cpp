//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitFileWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CFileWriterBase
//---------------------------------------------------------------------------

CFileWriterBase::CFileWriterBase(const std::wstring& FileName)
  : File_(FileName, std::fstream::binary | std::fstream::trunc) {
  buffer_ = std::vector<uint8_t>();
  if (!File_.is_open())
    throw std::runtime_error ("Cannot open ofstream\n");
}
//---------------------------------------------------------------------------

void CFileWriterBase::open(const std::wstring& FileName) {
  File_.open(FileName, std::fstream::binary | std::fstream::trunc);
  if (!File_.is_open())
    throw std::runtime_error ("Cannot open ofstream\n");
}
//---------------------------------------------------------------------------

void CFileWriterBase::close() {
  File_.close();
}
//---------------------------------------------------------------------------

bool CFileWriterBase::isOpen() const {
  return File_.is_open();
}

ssize_t CFileWriterBase::getCurSize() const {
    return curSize_;
}

void CFileWriterBase::fflush() {
      std::streamsize BlockSize = curSize_;
      File_.write(reinterpret_cast<const char*>(&buffer_), BlockSize);
      curSize_ = 0;
      //return curSize_;
}

void CFileWriterBase::writeBytes(std::vector<uint8_t> &object) {
    ssize_t sz = object.size();
    if (curSize_ + sz <= maxBufferSize) {
        std::copy(object.begin(), object.end(), buffer_.begin() + curSize_);
        curSize_ += sz;
    } else {
        ssize_t written = maxBufferSize - curSize_;
        std::copy(object.begin(), object.begin() + written, buffer_.begin() + curSize_);
        fflush();
        while ((sz - written) / maxBufferSize > 0) {
            auto begin = object.begin() + written;
            auto end = object.begin() + written + maxBufferSize;
            std::copy(begin, end, buffer_.begin() + curSize_);
            fflush();
            written += maxBufferSize;
        }
        std::copy(object.begin() + written, object.end(), buffer_.begin() + curSize_);
        curSize_ += sz - written;
    }
}

CFileWriterBase::~CFileWriterBase() {
    fflush();
}

//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
