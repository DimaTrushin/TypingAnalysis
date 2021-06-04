//---------------------------------------------------------------------------
#ifndef JSON_EXTENTION
#define JSON_EXTENTION
//---------------------------------------------------------------------------

#include "Kernel/Seance.h"
#include <iostream>
// https://github.com/nlohmann/json
#include <nlohmann/json.hpp>


namespace NSApplication {
namespace NSKernel {
template <typename BasicJsonType>
static void to_json(BasicJsonType& j, CKeyEvent C) {
    j["KeyID"] = C.getID();
    j["CKeyPosition"] = C.getPosition();
    j["KeyLabel"] = C.getLabel().unicode();
    QString KeyText = C.getText();
    std::vector<unsigned short> str;
    for (QChar t : KeyText) {
        str.push_back(t.unicode());
    }
    j["KeyText"] = str;
    j["PressingTime"] = C.getPressingTime().toMicroSecondsI();
    j["ReleasingTime"] = C.getReleasingTime().toMicroSecondsI();
}

template <typename BasicJsonType>
static void from_json(const BasicJsonType& j, CKeyEvent& C) {
    QString KeyText;
    std::vector<unsigned short> str = j["KeyText"].template get<std::vector<unsigned short>>();
    for (auto t : KeyText) {
        KeyText.push_back(QChar(t));
    }

    C = CKeyEvent(
            j["CKeyPosition"].template get<unsigned char>(),
            j["KeyID"].template get<unsigned char>(),
            QChar(j["KeyLabel"].template get<unsigned short>()),
            KeyText,
            MicroSeconds(j["PressingTime"].template get<long long>())
        );
    C.setReleasingTime(MicroSeconds(j["ReleasingTime"].template get<long long>()));
}

} // namespace NSKernel

} // namespace NSApplication


#endif // JSON_EXTENTION
