#include "SerializationLibrary/Tests.cpp"
#include "SerializationLibrary/FileWriter.h"


int main()
{
//    CKeyEventTest();
    ReadWriteKeyEventTest();
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
    ReadWriteBytesTest();
    ReadWriteBoolTest();
    ReadWriteShortTest();
    ReadWriteUnsignedShortTest();
    ReadWriteIntTest();
    ReadWriteUnsignedIntTest();
    ReadWriteLongTest();
    ReadWriteUnsignedLongTest();
    ReadWriteLongLongTest();
    ReadWriteUnsignedLongLongTest();
    ReadWriteFloatTest();
    ReadWriteDoubleTest();
    ReadWriteLongDoubleTest();
    ReadWriteCharTest();
    ReadWriteUnsignedCharTest();
    ReadWriteQCharTest();
    ReadWriteWCharTest();


    std::cout << "Done!\n";
    return 0;
}
