//---------------------------------------------------------------------------

#ifndef FILE_WRITER_H
#define FILE_WRITER_H
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
// from https://github.com/nlohmann/json
#include <nlohmann/json.hpp>
#include <boost/filesystem/fstream.hpp>

#include "JsonExtention.cpp"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Declaration of CFileWriterBase
//---------------------------------------------------------------------------

class CFileWriterBase {
public:
  CFileWriterBase() = default;
  CFileWriterBase(const std::wstring& FileName);
  void open(const std::wstring& FileName);
  void close();
  bool isOpen() const;
  ssize_t getCurSize() const;
  void fflush();
  void writeBytes(std::vector<uint8_t> &object);
  void addSize(ssize_t dif);
  static std::vector<uint8_t> toBytes(uint32_t size);
  static constexpr ssize_t maxBufferSize = 1000000; // 1e6;

protected:
  ~CFileWriterBase();
  ssize_t curSize_;
  boost::filesystem::ofstream File_;
  std::vector<uint8_t> buffer_;
};

class CFileWriter : public CFileWriterBase {
    using CBase = CFileWriterBase;
public:

    inline CFileWriter& operator<<(bool value);
    inline CFileWriter& operator<<(short value);
    inline CFileWriter& operator<<(unsigned short value);
    inline CFileWriter& operator<<(int value);
    inline CFileWriter& operator<<(unsigned int value);
    inline CFileWriter& operator<<(long value);
    inline CFileWriter& operator<<(unsigned long value);
    inline CFileWriter& operator<<(long long value);
    inline CFileWriter& operator<<(unsigned long long value);
    inline CFileWriter& operator<<(float value);
    inline CFileWriter& operator<<(double value);
    inline CFileWriter& operator<<(long double value);
    inline CFileWriter& operator<<(char value);
    inline CFileWriter& operator<<(unsigned char value);
    inline CFileWriter& operator<<(wchar_t value);


//    inline CFileWriter& operator<<(const std::string& String);
//    inline CFileWriter& operator<<(const std::wstring& String);
//    template<class TType1, class TType2>
//    inline CFileWriter& operator<<(const std::pair<TType1, TType2>& Pair);
//    template<class TType>
//    inline CFileWriter& operator<<(const std::vector<TType>& Vector);
//    template<class TType>
//    inline CFileWriter& operator<<(const std::deque<TType>& Deque);
//    template<class TType>
//    inline CFileWriter& operator<<(const std::list<TType>& List);
//    template<class TType, size_t TSize>
//    inline CFileWriter& operator<<(const std::array<TType, TSize>& Array);
//    template<class TKey, class TType, class TCompare>
//    inline CFileWriter& operator<<(const std::map<TKey, TType, TCompare>& Map);
//    template<class TType, class TContainer>
//    inline CFileWriter& operator<<(const std::queue<TType, TContainer>& Queue);
//    template<class TType, class TContainer, class TCompare>
//    inline CFileWriter& operator<<(
//                    const std::priority_queue<TType,
//                                              TContainer,
//                                              TCompare>& PriorityQueue);

};
//---------------------------------------------------------------------------
// Definition of CFileWriter
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(bool value) {
    nlohmann::json j = nlohmann::json(value);
    std::vector<uint8_t> v_ubson =  nlohmann::json::to_ubjson(j);
    std::vector<uint8_t> sizeBytes = toBytes(v_ubson.size());
    this->writeBytes(sizeBytes);
    this->writeBytes(v_ubson);
    return *this;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif //FILE_WRITER_H
