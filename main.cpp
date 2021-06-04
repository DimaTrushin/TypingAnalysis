#include "SerializationLibrary/JsonExtention.cpp"
#include "SerializationLibrary/Tests.cpp"
#include "SerializationLibrary/FileWriter.h"


int main()
{
    CKeyEventTest();
    BoolTest();
    CharTest();
    UnsignedCharTest();
    ShortTest();
    UnsignedShortTest();
    IntTest();
    UnsignedIntTest();
    LongTest();
    UnsignedLongTest();
    LongLongTest();
    UnsignedLongLongTest();
    WCharTest();
    BytesConvertionTest();
    ReadWriteTest();


    std::cout << "Done!\n";
    return 0;
}
