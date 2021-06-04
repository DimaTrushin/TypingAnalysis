//---------------------------------------------------------------------------

#ifndef UnitFileReaderH
#define UnitFileReaderH
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
protected:
  ~CFileReaderBase() = default;
  boost::filesystem::ifstream File_;
  //std::ifstream File_;
  std::vector<char> buffer_;
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
  //inline CFileReader& operator>>(void*& value);

  inline CFileReader& operator>>(std::string& String);
  inline CFileReader& operator>>(std::wstring& String);
  template<class TType1, class TType2>
  inline CFileReader& operator>>(std::pair<TType1, TType2>& Pair);
  template<class TType>
  inline CFileReader& operator>>(std::vector<TType>& Vector);
  template<class TType>
  inline CFileReader& operator>>(std::deque<TType>& Deque);
  template<class TType>
  inline CFileReader& operator>>(std::list<TType>& List);
  template<class TType, size_t TSize>
  inline CFileReader& operator>>(std::array<TType, TSize>& Array);
  template<class TKey, class TType, class TCompare>
  inline CFileReader& operator>>(std::map<TKey, TType, TCompare>& Map);
  template<class TType, class TContainer>
  inline CFileReader& operator>>(std::queue<TType, TContainer>& Queue);
  template<class TType, class TContainer, class TCompare>
  inline CFileReader& operator>>(
                        std::priority_queue<TType,
                                            TContainer,
                                            TCompare>& PriorityQueue);


};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
