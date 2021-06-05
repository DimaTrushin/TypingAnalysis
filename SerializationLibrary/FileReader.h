//---------------------------------------------------------------------------

#ifndef FILE_READER_H
#define FILE_READER_H
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <string>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <map>
#include <queue>
#include <type_traits>
// from https://github.com/nlohmann/json
#include <nlohmann/json.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <iostream>
#include <QChar>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CFileReaderBase
//---------------------------------------------------------------------------

class CFileReaderBase {
public:
    CFileReaderBase() = default;
    CFileReaderBase(const std::wstring& FileName);
    void open(const std::wstring& FileName);
    void close();
    bool isOpen() const;
    ssize_t getCurPos() const;

    void readBytes(std::vector<uint8_t> &object, intmax_t size);
    static uint32_t toSize(std::vector<uint8_t>& bytes);
    static constexpr ssize_t maxBufferSize = 1000000; // 1e6;

protected:
    void load();
    ~CFileReaderBase();
    boost::filesystem::ifstream File_;
    std::vector<uint8_t> buffer_;
    ssize_t curPos_;
    intmax_t filePos_;
    intmax_t fileSize_;
};

//---------------------------------------------------------------------------
// Declaration of CFileReader
//---------------------------------------------------------------------------

class CFileReader : public CFileReaderBase {
    using CBase = CFileReaderBase;
public:
    using CBase::CBase;

    inline CFileReader& operator>>(bool& value);
    inline CFileReader& operator>>(short& value);
    inline CFileReader& operator>>(unsigned short& value);
    inline CFileReader& operator>>(int& value);
    inline CFileReader& operator>>(unsigned int& value);
    inline CFileReader& operator>>(long& value);
    inline CFileReader& operator>>(unsigned long& value);
    inline CFileReader& operator>>(long long& value);
    inline CFileReader& operator>>(unsigned long long& value);
    inline CFileReader& operator>>(float& value);
    inline CFileReader& operator>>(double& value);
    inline CFileReader& operator>>(long double& value);
    inline CFileReader& operator>>(char& value);
    inline CFileReader& operator>>(unsigned char& value);
    inline CFileReader& operator>>(wchar_t& value);
    inline CFileReader& operator>>(QChar& value);

    //  inline CFileReader& operator>>(std::string& String);
    //  inline CFileReader& operator>>(std::wstring& String);
    //  template<class TType1, class TType2>
    //  inline CFileReader& operator>>(std::pair<TType1, TType2>& Pair);
    //  template<class TType>
    //  inline CFileReader& operator>>(std::vector<TType>& Vector);
    //  template<class TType>
    //  inline CFileReader& operator>>(std::deque<TType>& Deque);
    //  template<class TType>
    //  inline CFileReader& operator>>(std::list<TType>& List);
    //  template<class TType, size_t TSize>
    //  inline CFileReader& operator>>(std::array<TType, TSize>& Array);
    //  template<class TKey, class TType, class TCompare>
    //  inline CFileReader& operator>>(std::map<TKey, TType, TCompare>& Map);
    //  template<class TType, class TContainer>
    //  inline CFileReader& operator>>(std::queue<TType, TContainer>& Queue);
    //  template<class TType, class TContainer, class TCompare>
    //  inline CFileReader& operator>>(
    //                        std::priority_queue<TType,
    //                                            TContainer,
    //                                            TCompare>& PriorityQueue);
protected:
    template<class TPODType>
    inline void readPOD(CFileReader* fr, TPODType* pData);

};

//---------------------------------------------------------------------------

template<class TPODType>
void CFileReader::readPOD(CFileReader* fr, TPODType* pData) {
    std::vector<uint8_t> sizeBytes;
    fr->readBytes(sizeBytes, 4);
    uint32_t size = CFileReader::toSize(sizeBytes);
    std::vector<uint8_t> v_ubson;
    fr->readBytes(v_ubson, size);

    nlohmann::json j_from_ubson = nlohmann::json::from_ubjson(v_ubson);
    *pData = j_from_ubson.template get<TPODType>();
}

//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(bool& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(short& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned short& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}

//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(int& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned int& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(long& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned long& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(long long& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned long long& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(float& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(double& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(long double& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(char& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned char& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}

//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(wchar_t& value) {
    CFileReader::readPOD(this, &value);
    return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(QChar& value) {
    unsigned short x;
    *this >> x;
    value = QChar(x);
    return *this;
}

//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif //FILE_READER_H
