#include "SerializationLibrary/JsonExtention.cpp"

//j = BasicJsonType{{"age", p.m_age}, {"name", p.m_name}, {"country", p.m_country}};



void test() {
    NSApplication::NSKeyboard::CKeyPosition KeyPosition = NSApplication::NSKeyboard::CKeyPosEnum::ESC;
    NSApplication::NSKeyboard::CKeyID KeyID = NSApplication::NSKeyboard::CKeyIDEnum::Esc;
    QChar KeyLabel = 'b';
    QString KeyText = "aa";
    NSApplication::CTime PressingTime = NSApplication::CTime();
    NSApplication::NSKernel::CKeyEvent kevt =
            NSApplication::NSKernel::CKeyEvent(KeyPosition, KeyID, KeyLabel,KeyText, PressingTime);

    nlohmann::json j = nlohmann::json(kevt);
    KeyLabel = 'a';
    NSApplication::NSKernel::CKeyEvent kevt2 = NSApplication::NSKernel::CKeyEvent(KeyPosition, KeyID, KeyLabel,KeyText, PressingTime);;
    kevt2 = j.template get<NSApplication::NSKernel::CKeyEvent>();
    std::cout << kevt.isSameKey(kevt2) << std::endl;

    std::cout << j.dump(4) << std::endl;
}


int main()
{
       test();
       return 0;
}
