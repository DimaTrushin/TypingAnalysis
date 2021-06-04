//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "FileWriter.h"
#include <iostream>
#include <algorithm>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CFileWriterBase
//---------------------------------------------------------------------------

CFileWriterBase::CFileWriterBase(const std::wstring& FileName)
    : File_(FileName, std::fstream::binary | std::fstream::trunc) {
    buffer_ = std::vector<uint8_t>(maxBufferSize);
    curSize_ = 0;
    if (!File_.is_open())
        throw std::runtime_error ("Cannot open ofstream\n");
}
//---------------------------------------------------------------------------

void CFileWriterBase::open(const std::wstring& FileName) {
    File_.open(FileName, std::fstream::binary | std::fstream::trunc);
    buffer_ = std::vector<uint8_t>(maxBufferSize);
    curSize_ = 0;
    if (!File_.is_open())
        throw std::runtime_error ("Cannot open ofstream\n");
}
//---------------------------------------------------------------------------

void CFileWriterBase::close() {
    fflush();
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
    if (getCurSize() == 0) {
        return;
    }
    std::streamsize BlockSize = getCurSize();
    const char *ptr = (char*)buffer_.data();
    File_.write(ptr, BlockSize);
    curSize_ = 0;
}


void CFileWriterBase::addSize(ssize_t dif) {
    curSize_ = curSize_ + dif;
}

void CFileWriterBase::writeBytes(std::vector<uint8_t> &object) {
    ssize_t sz = object.size();
    if (getCurSize() + sz <= maxBufferSize) {
        std::copy(object.begin(), object.end(), buffer_.begin() + getCurSize());
        addSize(sz);
    } else {
        ssize_t written = maxBufferSize - curSize_;
        std::copy(object.begin(), object.begin() + written, buffer_.begin() + curSize_);
        addSize(written);
        fflush();
        while ((sz - written) / maxBufferSize > 0) {
            auto begin = object.begin() + written;
            auto end = object.begin() + written + maxBufferSize;
            std::copy(begin, end, buffer_.begin() + curSize_);
            addSize(maxBufferSize);
            fflush();
            written += maxBufferSize;
        }
        std::copy(object.begin() + written, object.end(), buffer_.begin() + curSize_);
        addSize(sz - written);
    }
}

CFileWriterBase::~CFileWriterBase() {
    close();
}

std::vector<uint8_t> CFileWriterBase::toBytes(uint32_t size) {
    std::vector<uint8_t> res = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
        int shift = i * 8;
        res[i] = (size >> shift);
    }
    return res;
}

//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
