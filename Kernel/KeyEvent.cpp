#include "KeyEvent.h"

namespace NSApplication {
namespace NSKernel {

CKeyEvent::CKeyEvent(CKeyPosition KeyPosition, CKeyID KeyID, QChar KeyLabel,
                     QString KeyText, CTime PressingTime)
    : KeyPosition_(KeyPosition), KeyID_(KeyID), KeyLabel_(KeyLabel),
      KeyText_(KeyText), PressingTime_(PressingTime),
      ReleasingTime_(PressingTime_) {
}

CKeyEvent::CKeyEvent(const CKeyEvent::CKeyPressing& PressingEvent)
    : CKeyEvent(PressingEvent.KeyPosition, PressingEvent.KeyID,
                PressingEvent.KeyLabel, PressingEvent.KeyText,
                PressingEvent.Time) {
}

CKeyEvent::CKeyEvent() {
    NSApplication::NSKeyboard::CKeyPosition KeyPosition = NSApplication::NSKeyboard::CKeyPosEnum::ESC;
    NSApplication::NSKeyboard::CKeyID KeyID = NSApplication::NSKeyboard::CKeyIDEnum::Esc;
    QChar KeyLabel = 'a';
    QString KeyText = "a";
    NSApplication::CTime PressingTime = NSApplication::CTime();
    NSApplication::NSKernel::CKeyEvent kevt =
            NSApplication::NSKernel::CKeyEvent(KeyPosition, KeyID, KeyLabel,KeyText, PressingTime);
}

void CKeyEvent::setReleasingTime(CTime ReleasingTime) {
  ReleasingTime_ = ReleasingTime;
}

bool CKeyEvent::isSameKey(const CKeyEvent& KeyEvent) const {
  return KeyPosition_ == KeyEvent.KeyPosition_;
}

CKeyEvent::CKeyPosition CKeyEvent::getPosition() const {
  return KeyPosition_;
}

CKeyEvent::CKeyID CKeyEvent::getID() const {
  return KeyID_;
}

QChar CKeyEvent::getLabel() const {
  return KeyLabel_;
}

QString CKeyEvent::getText() const {
  return KeyText_;
}

CTime CKeyEvent::getPressingTime() const {
  return PressingTime_;
}

CTime CKeyEvent::getReleasingTime() const {
  return ReleasingTime_;
}

CTime CKeyEvent::getDuration() const {
  return ReleasingTime_ - PressingTime_;
}

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

CKeyEvent::CFileReader& operator>>(CKeyEvent::CFileReader& FileReader, CKeyEvent& KeyEvent) {
    std::vector<uint8_t> sizeBytes;
    FileReader.readBytes(sizeBytes, 4);
    uint32_t size = FileReader.toSize(sizeBytes);
    std::vector<uint8_t> v_ubson;
    FileReader.readBytes(v_ubson, size);

    nlohmann::json j_from_ubson = nlohmann::json::from_ubjson(v_ubson);
    KeyEvent = j_from_ubson.template get<NSApplication::NSKernel::CKeyEvent>();
    return FileReader;
}

CKeyEvent::CFileWriter& operator<<(CKeyEvent::CFileWriter& FileWriter, const CKeyEvent& KeyEvent) {
    nlohmann::json j = nlohmann::json(KeyEvent);
    std::vector<uint8_t> v_ubson =  nlohmann::json::to_ubjson(j);
    std::vector<uint8_t> sizeBytes = FileWriter.toBytes(v_ubson.size());
    FileWriter.writeBytes(sizeBytes);
    FileWriter.writeBytes(v_ubson);
    return FileWriter;
}


} // namespace NSKernel
} // namespace NSApplication
