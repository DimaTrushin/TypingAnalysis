//---------------------------------------------------------------------------

#ifndef UnitJsonWriterH
#define UnitJsonWriterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <string>
//#include <vector>
#include <deque>
#include <list>
#include <array>
#include <map>
#include <queue>
// https://github.com/nlohmann/json
#include <nlohmann/json.hpp>
#include <QChar>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

class CJsonWriter {
public:
    CJsonWriter() = default;

    inline CJsonWriter& write(bool value, std::string& name);
    inline CJsonWriter& write(short value, std::string& name);
    inline CJsonWriter& write(unsigned short value, std::string& name);
    inline CJsonWriter& write(int value, std::string& name);
    inline CJsonWriter& write(unsigned int value, std::string& name);
    inline CJsonWriter& write(long value, std::string& name);
    inline CJsonWriter& write(unsigned long value, std::string& name);
    inline CJsonWriter& write(long long value, std::string& name);
    inline CJsonWriter& write(unsigned long long value, std::string& name);
    inline CJsonWriter& write(float value, std::string& name);
    inline CJsonWriter& write(double value, std::string& name);
    inline CJsonWriter& write(long double value, std::string& name);
    inline CJsonWriter& write(char value, std::string& name);
    inline CJsonWriter& write(unsigned char value, std::string& name);
    inline CJsonWriter& write(wchar_t value, std::string& name);
    inline CJsonWriter& write(QChar value, std::string& name);


//    void write(const QString& QString, std::string& name);
//    void write(const std::string& String, std::string& name);
//    void write(const std::wstring& String, std::string& name);
//    template<class TType1, class TType2>
//    void write(const std::pair<TType1, TType2>& Pair, std::string& name);
//    template<class TType>
//    void write(const std::vector<TType>& Vector, std::string& name);
//    template<class TType>
//    void write(const std::deque<TType>& Deque, std::string& name);
//    template<class TType>
//    void write(const std::list<TType>& List, std::string& name);
//    template<class TType, size_t TSize>
//    void write(const std::array<TType, TSize>& Array, std::string& name);
//    template<class TKey, class TType, class TCompare>
//    void write(const std::map<TKey, TType, TCompare>& Map, std::string& name);
//    template<class TType, class TContainer>
//    void write(const std::queue<TType, TContainer>& Queue, std::string& name);
//    template<class TType, class TContainer, class TCompare>
//    void write(const std::priority_queue<TType,
//               TContainer,
//               TCompare>& PriorityQueue, std::string& name);

protected:
  ~CJsonWriter() = default;
  nlohmann::json json_;
};

inline CJsonWriter& write(bool value, std::string& name) {

}

//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
