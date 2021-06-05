#ifndef JSON_TESTS
#define JSON_TESTS

#include "FileWriter.h"
#include "FileReader.h"
#include "Kernel/KeyEvent.h"

//void CKeyEventTest() {
//    NSApplication::NSKernel::CKeyEvent testKeyEvent;
//    NSApplication::NSKernel::CKeyEvent testKeyEvent2;

//    nlohmann::json j = nlohmann::json(testKeyEvent);
//    testKeyEvent2 = j.template get<NSApplication::NSKernel::CKeyEvent>();

//    assert(testKeyEvent.isSameKey(testKeyEvent2) == 1);
//}

void BoolTest() {
    bool testBool = true;
    bool testBool2 = false;

    nlohmann::json j = nlohmann::json(testBool);
    testBool2 = j.template get<bool>();

    assert(testBool == testBool2);
}

void CharTest() {
    char testChar = CHAR_MAX;
    char testChar2 = 0;

    nlohmann::json j = nlohmann::json(testChar);
    testChar2 = j.template get<char>();

    assert(testChar ==  testChar2);
}

void UnsignedCharTest() {
    unsigned char testUnsignedChar = UCHAR_MAX;
    unsigned char testUnsignedChar2 = 0;

    nlohmann::json j = nlohmann::json(testUnsignedChar);
    testUnsignedChar2 = j.template get<unsigned short>();

    assert(testUnsignedChar == testUnsignedChar2);
}

void ShortTest() {
    short testShort = SHRT_MAX;
    short testShort2 = 0;

    nlohmann::json j = nlohmann::json(testShort);
    testShort2 = j.template get<short>();

    assert(testShort ==  testShort2);
}

void UnsignedShortTest() {
    unsigned short testUnsignedShort = USHRT_MAX;
    unsigned short testUnsignedShort2 = 0;

    nlohmann::json j = nlohmann::json(testUnsignedShort);
    testUnsignedShort2 = j.template get<unsigned short>();

    assert(testUnsignedShort == testUnsignedShort2);
}

void IntTest() {
    int testInt = INT_MAX;
    int testInt2 = 0;

    nlohmann::json j = nlohmann::json(testInt);
    testInt2 = j.template get<int>();

    assert(testInt ==  testInt2);
}

void UnsignedIntTest() {
    unsigned int testUnsignedInt = UINT_MAX;
    unsigned int testUnsignedInt2 = 0;

    nlohmann::json j = nlohmann::json(testUnsignedInt);
    testUnsignedInt2 = j.template get<unsigned int>();

    assert(testUnsignedInt == testUnsignedInt2);
}

void LongTest() {
    long testLong = LONG_MAX;
    long testLong2 = 0;

    nlohmann::json j = nlohmann::json(testLong);
    testLong2 = j.template get<long>();

    assert(testLong ==  testLong2);
}

void UnsignedLongTest() {
    unsigned long testUnsignedLong = ULONG_MAX;
    unsigned long testUnsignedLong2 = 0;

    nlohmann::json j = nlohmann::json(testUnsignedLong);
    testUnsignedLong2 = j.template get<unsigned long>();

    assert(testUnsignedLong == testUnsignedLong2);
}

void LongLongTest() {
    long long testLongLong = LLONG_MAX;
    long long testLongLong2 = 0;

    nlohmann::json j = nlohmann::json(testLongLong);
    testLongLong2 = j.template get<long long>();

    assert(testLongLong ==  testLongLong2);
}

void UnsignedLongLongTest() {
    unsigned long long testUnsignedLongLong = ULLONG_MAX;
    unsigned long long testUnsignedLongLong2 = 0;

    nlohmann::json j = nlohmann::json(testUnsignedLongLong);
    testUnsignedLongLong2 = j.template get<unsigned long long>();

    assert(testUnsignedLongLong == testUnsignedLongLong2);
}


void WCharTest() {
    wchar_t testWchar = L"ሰ"[0];
    wchar_t testWchar2 = 0;

    nlohmann::json j = nlohmann::json(testWchar);
    testWchar2 = j.template get<wchar_t>();

    assert(testWchar == testWchar2);
}

void BytesConvertionTest() {
    uint32_t number = 234234234;

    std::vector<uint8_t> bytes = NSApplication::NSLibrary::CFileWriter::toBytes(number);
    uint32_t number2 = NSApplication::NSLibrary::CFileReader::toSize(bytes);

    assert(number == number2);
}

void ReadWriteBytesTest() {
    const std::wstring file = L"abs.txt";
    intmax_t size = 4500000;
    std::vector<uint8_t> a(size, 3);
    std::vector<uint8_t> b;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f.writeBytes(a);
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf.readBytes(b, size);
    rf.close();

    assert(a == b);
}

void ReadWriteBoolTest() {
    const std::wstring file = L"abs.txt";

    bool test = true;
    bool test2 = true;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteShortTest() {
    const std::wstring file = L"abs.txt";

    short test = SHRT_MAX;
    short test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteUnsignedShortTest() {
    const std::wstring file = L"abs.txt";

    unsigned short test = USHRT_MAX;
    unsigned short test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteIntTest() {
    const std::wstring file = L"abs.txt";

    int test = INT_MAX;
    int test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteUnsignedIntTest() {
    const std::wstring file = L"abs.txt";

    unsigned int test = UINT_MAX;
    unsigned int test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteLongTest() {
    const std::wstring file = L"abs.txt";

    long test = LONG_MAX;
    long test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteUnsignedLongTest() {
    const std::wstring file = L"abs.txt";

    unsigned long test = ULONG_MAX;
    unsigned long test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteLongLongTest() {
    const std::wstring file = L"abs.txt";

    long long test = LLONG_MAX;
    long long test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteUnsignedLongLongTest() {
    const std::wstring file = L"abs.txt";

    unsigned long long test = ULLONG_MAX;
    unsigned long long test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteFloatTest() {
    const std::wstring file = L"abs.txt";

    float test = 0.5;
    float test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteDoubleTest() {
    const std::wstring file = L"abs.txt";

    double test = 0.5;
    double test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteLongDoubleTest() {
    const std::wstring file = L"abs.txt";

    long double test = 0.5;
    long double test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteCharTest() {
    const std::wstring file = L"abs.txt";

    char test = CHAR_MAX;
    char test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteUnsignedCharTest() {
    const std::wstring file = L"тест";

    unsigned char test = UCHAR_MAX;
    unsigned char test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteQCharTest() {
    const std::wstring file = L"тест";

    QChar test = 'a';
    QChar test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteWCharTest() {
    const std::wstring file = L"тест";

    wchar_t test = L"ሰ"[0];
    wchar_t test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test == test2);
}

void ReadWriteKeyEventTest() {
    const std::wstring file = L"тест";
    NSApplication::NSKernel::CKeyEvent test;
    NSApplication::NSKernel::CKeyEvent test2 = test;

    NSApplication::NSLibrary::CFileWriter f;
    f.open(file);
    f << test;
    f.close();

    NSApplication::NSLibrary::CFileReader rf;
    rf.open(file);
    rf >> test;
    rf.close();

    assert(test.isSameKey(test2));
}

#endif // JSON_TESTS
