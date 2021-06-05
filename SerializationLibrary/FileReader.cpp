//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "FileReader.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CFileReaderBase
//---------------------------------------------------------------------------

CFileReaderBase::CFileReaderBase(const std::wstring& FileName)
    : File_(FileName, std::fstream::binary) {
    if (!File_.is_open())
        throw std::runtime_error  ("Cannot open ifstream\n");
    auto p = boost::filesystem::path{FileName};
    buffer_ = std::vector<uint8_t>(maxBufferSize);
    fileSize_ = boost::filesystem::file_size(p);
    curPos_ = maxBufferSize;
    filePos_ = 0;
}
//---------------------------------------------------------------------------

void CFileReaderBase::open(const std::wstring& FileName) {
    File_.open(FileName, std::fstream::binary);
    if (!File_.is_open())
        throw std::runtime_error ("Cannot open ifstream\n");
    auto p = boost::filesystem::path{FileName};
    fileSize_ = boost::filesystem::file_size(p);
    curPos_ = maxBufferSize;
    filePos_ = 0;
    buffer_ = std::vector<uint8_t>(maxBufferSize);
}
//---------------------------------------------------------------------------

void CFileReaderBase::close() {
    File_.close();
}

CFileReaderBase::~CFileReaderBase() {
    close();
}
//---------------------------------------------------------------------------

bool CFileReaderBase::isOpen() const {
    return File_.is_open();
}

ssize_t CFileReaderBase::getCurPos() const {
    return curPos_;
}


uint32_t CFileReaderBase::toSize(std::vector<uint8_t>& bytes) {
    uint32_t size = 0;
    for (int i = 4 - 1; i >= 0; --i) {
        size = size << 8;
        size += bytes[i];
    }
    return size;
}

void  CFileReaderBase::load() {
    ssize_t toRead = std::min(fileSize_ - filePos_, (intmax_t)maxBufferSize);
    if (toRead == 0) {
        throw std::runtime_error ("End of file, nothing to read\n");
    }
    filePos_ += toRead;
    curPos_ = maxBufferSize - toRead;
    char *ptr = ((char*)buffer_.data() + curPos_);
    std::streamsize BlockSize = toRead;
    File_.read(ptr, BlockSize);

}

void CFileReaderBase::readBytes(std::vector<uint8_t> &object, intmax_t size) {
    if (object.size() < size) {
        object.resize(size);
    }
    if (curPos_ + size <= maxBufferSize) {
        auto begin = buffer_.begin() + curPos_;
        std::copy(begin, begin + size, object.begin());
        curPos_ += size;
    } else {
        intmax_t read = maxBufferSize - curPos_;
        auto begin = buffer_.begin() + curPos_;
        std::copy(begin, begin + read, object.begin());
        curPos_ += read;
        load();
        while ((size - read) / maxBufferSize > 0) {
            auto objectIt = object.begin() + read;
            std::copy(buffer_.begin(), buffer_.end(), objectIt);
            curPos_ += maxBufferSize;
            load();
            read += maxBufferSize;
        }

        intmax_t left = size - read;
        auto objectIt = object.begin() + read;
        std::copy(buffer_.begin() + curPos_, buffer_.begin() + curPos_ + left, objectIt);
        curPos_ += left;
    }
}

//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------



