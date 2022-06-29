#include "SeanceManager.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/filesystem/fstream.hpp>

#include <algorithm>

#include <QDebug>

namespace NSApplication {
namespace NSKernel {

namespace NSSeanceManagerDetail {

CSeanceManagerImpl::CSeanceManagerImpl()
    : KeyPressingInput_(
          [this](const CKeyPressing& KeyPressing) { handle(KeyPressing); }),
      KeyReleasingInput_(
          [this](const CKeyReleasing& KeyReleasing) { handle(KeyReleasing); }),
      CurrentSeanceOutput_(
          [this]() -> CSeanceGetType { return CurrentSeance_; }) {
}

NSLibrary::CObserver<CSeanceManagerImpl::CKeyPressing>*
CSeanceManagerImpl::pressingInput() {
  return &KeyPressingInput_;
}

NSLibrary::CObserver<CSeanceManagerImpl::CKeyReleasing>*
CSeanceManagerImpl::releasingInput() {
  return &KeyReleasingInput_;
}

void CSeanceManagerImpl::subscribeToCurrentSeance(CSeanceObserver* observer) {
  CurrentSeanceOutput_.subscribe(observer);
}

void CSeanceManagerImpl::makeSessions() {
  if (SeanceMaker_.transferTo(&CurrentSeance_))
    CurrentSeanceOutput_.notify();
}

void CSeanceManagerImpl::saveFile(const QString& Path) {
  // TO DO
  qDebug() << "saveFile";
  boost::filesystem::ofstream ofs(Path.toStdWString(),
                                  std::fstream::binary | std::fstream::trunc);
  boost::archive::binary_oarchive arch(ofs);
  arch << CurrentSeance_;
}

void CSeanceManagerImpl::loadFile(const QString& Path) {
  // TO DO
  qDebug() << "loadFile";
  try {
    boost::filesystem::ifstream ifs(Path.toStdWString(), std::fstream::binary);
    boost::archive::binary_iarchive arch(ifs);
    CSeance Tmp;
    arch >> Tmp;
    for (auto& session : Tmp)
      CurrentSeance_.emplace_back(std::move(session));
    CurrentSeanceOutput_.notify();
  } catch (...) {
    // Unsupported File
  }
}

void CSeanceManagerImpl::handle(const CKeyPressing& KeyPressing) {
  switch (KeyPressing.KeyID) {
    using CKeyIDEnum = NSKeyboard::CKeyIDEnum;
  case CKeyIDEnum::Esc:
    makeSessions();
    break;
  default:
    SeanceMaker_.add(KeyPressing);
  }
}

void CSeanceManagerImpl::handle(const CKeyReleasing& KeyReleasing) {
  SeanceMaker_.add(KeyReleasing);
}
} // namespace NSSeanceManagerDetail

} // namespace NSKernel
} // namespace NSApplication
