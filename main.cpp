#include "SerializationLibrary/JsonExtention.cpp"
#include "SerializationLibrary/JsonTests.cpp"
#include "SerializationLibrary/UnitFileWriter.h"


int main()
{
//       CKeyEventTest();
//       BoolTest();
//       CharTest();
//       UnsignedCharTest();
//       ShortTest();
//       UnsignedShortTest();
//       IntTest();
//       UnsignedIntTest();
//       LongTest();
//       UnsignedLongTest();
//       LongLongTest();
//       UnsignedLongLongTest();
//       WCharTest();



//        boost::filesystem::ofstream File;
        const std::wstring file = L"abs.txt";
//        File.open(file);
        std::vector<uint8_t> a(5000000, 3);
//        const char *ptr = (char*)a.data();
//        std::streamsize BlockSize = 990000;
//        File.write(ptr, BlockSize);
//        File.write(ptr, BlockSize + 1);
//        File.close();

       NSApplication::NSLibrary::CFileWriter f;


       f.open(file);
       f.writeBytes(a);
       f.close();
       std::cout << "Done!\n";
       return 0;
}
