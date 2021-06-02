#include "SerializationLibrary/JsonExtention.cpp"
#include "SerializationLibrary/JsonTests.cpp"


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
       std::cout << "Done!\n";
       return 0;
}
