#ifndef NSAPPLICATION_CFILEHANDLERS_H
#define NSAPPLICATION_CFILEHANDLERS_H

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/filesystem/fstream.hpp>

#include <optional>

#include <QString>

namespace NSApplication {

namespace NSFileHandlersDetail {

class CReaderDefines {
public:
  using CStream = boost::filesystem::ifstream;
  using COptionalStream = std::optional<CStream>;
  using CArchive = boost::archive::binary_iarchive;
  using COptionalArchive = std::optional<CArchive>;

  static constexpr std::ios::openmode Flags = std::fstream::binary;
};

class CWriterDefines {
public:
  using CStream = boost::filesystem::ofstream;
  using COptionalStream = std::optional<CStream>;
  using CArchive = boost::archive::binary_oarchive;
  using COptionalArchive = std::optional<CArchive>;

  static constexpr std::ios::openmode Flags =
      std::fstream::binary | std::fstream::trunc;
};

template<class TBase>
class CStreamHolder : protected TBase {
  using CBase = TBase;

public:
  using CStream = typename CBase::CStream;
  using COptionalStream = typename CBase::COptionalStream;

public:
  bool isOpen() const {
    return Stream_.has_value() && Stream_->is_open();
  }
  void open(const QString& Path) {
    open_(Path);
  }
  void close() {
    close_();
  }

protected:
  const CStream& stream_() const {
    return *Stream_;
  }
  CStream& stream_() {
    return *Stream_;
  }

private:
  void open_(const QString& Path) {
    try {
      Stream_.emplace(Path.toStdWString(), CBase::Flags);
    } catch (...) {
    }
  }

  void close_() {
    Stream_.reset();
  }

  COptionalStream Stream_;
};

template<class TBase>
class CArchiveHolder : protected TBase {
  using CBase = TBase;

public:
  using CArchive = typename CBase::CArchive;
  using COptionalArchive = typename CBase::COptionalArchive;

  bool isOpen() const {
    return Archive_.has_value();
  }
  void open(const QString& Path) {
    close();
    CBase::open(Path);
    if (!CBase::isOpen()) {
      return;
    }
    open_();
    if (!isOpen())
      CBase::close();
  }
  void close() {
    close_();
    CBase::close();
  }

protected:
  const CArchive& archive_() const {
    return *Archive_;
  }
  CArchive& archive_() {
    return *Archive_;
  }

private:
  void open_() {
    try {
      Archive_.emplace(CBase::stream_());
    } catch (...) {
    }
  }
  void close_() {
    Archive_.reset();
  }
  COptionalArchive Archive_;
};

using CFileReaderBase = CArchiveHolder<CStreamHolder<CReaderDefines>>;
using CFileWriterBase = CArchiveHolder<CStreamHolder<CWriterDefines>>;

} // namespace NSFileHandlersDetail

class CFileReader : public NSFileHandlersDetail::CFileReaderBase {
  using CBase = NSFileHandlersDetail::CFileReaderBase;

public:
  template<class T>
  CFileReader& operator>>(T& data) {
    CBase::archive_() >> data;
    return *this;
  }
};
class CFileWriter : public NSFileHandlersDetail::CFileWriterBase {
  using CBase = NSFileHandlersDetail::CFileWriterBase;

public:
  template<class T>
  CFileWriter& operator<<(const T& data) {
    CBase::archive_() << data;
    return *this;
  }
};
} // namespace NSApplication

#endif // NSAPPLICATION_CFILEHANDLERS_H
