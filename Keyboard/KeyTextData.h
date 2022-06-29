#ifndef NSAPPLICATION_NSKEYBOARD_CKEYTEXTDATA_H
#define NSAPPLICATION_NSKEYBOARD_CKEYTEXTDATA_H

#include <QChar>
#include <boost/serialization/access.hpp>

namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive& arch, QChar& ch, const unsigned int) {
  arch& ch.unicode();
}

} // namespace serialization
} // namespace boost

namespace NSApplication {
namespace NSKeyboard {

struct CLabelData {
  QChar LowSymbol;
  QChar HighSymbol;
  unsigned char Size;

private:
  friend boost::serialization::access;
  template<class TArchive>
  void serialize(TArchive& arch, const unsigned int) {
    arch& LowSymbol;
    arch& HighSymbol;
    arch& Size;
  }
};

struct CKeyTextData {
  QChar Symbol[2];
  unsigned char Size;

private:
  friend boost::serialization::access;
  template<class TArchive>
  void serialize(TArchive& arch, const unsigned int) {
    arch& Symbol;
    arch& Size;
  }
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYTEXTDATA_H
