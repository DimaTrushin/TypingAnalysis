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


       const std::wstring file = L"abs.txt";
       NSApplication::NSLibrary::CFileWriter f;
       f.open(file);

       bool test = true;
       f << test;
       f.close();

       std::cout << "Done!\n";
       return 0;
}
