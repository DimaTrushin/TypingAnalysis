#ifndef JSON_TESTS
#define JSON_TESTS

#include "SerializationLibrary/JsonExtention.cpp"

void CKeyEventTest() {
    NSApplication::NSKernel::CKeyEvent testKeyEvent;
    NSApplication::NSKernel::CKeyEvent testKeyEvent2;

    nlohmann::json j = nlohmann::json(testKeyEvent);
    testKeyEvent2 = j.template get<NSApplication::NSKernel::CKeyEvent>();

    assert(testKeyEvent.isSameKey(testKeyEvent2) == 1);
}

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

    assert(testWchar2 == testWchar);
}

#endif // JSON_TESTS
