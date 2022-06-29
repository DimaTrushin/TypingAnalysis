#ifndef NSAPPLICATION_CTIMEAPP_H
#define NSAPPLICATION_CTIMEAPP_H

#include <boost/serialization/access.hpp>

namespace NSApplication {

class CTime {
  friend boost::serialization::access;

public:
  CTime() = default;

  static CTime MicroSeconds(long long microseconds);
  static CTime MilliSeconds(long long milliseconds);
  static CTime Seconds(long long seconds);

  friend CTime operator+(const CTime& first, const CTime& second);
  friend CTime operator-(const CTime& first, const CTime& second);
  CTime& operator+=(const CTime& other);
  CTime& operator-=(const CTime& other);

  friend bool operator<(const CTime& first, const CTime& second);
  friend bool operator>(const CTime& first, const CTime& second);
  friend bool operator<=(const CTime& first, const CTime& second);
  friend bool operator>=(const CTime& first, const CTime& second);
  friend bool operator==(const CTime& first, const CTime& second);
  friend bool operator!=(const CTime& first, const CTime& second);
  CTime operator-() const;

  long long toMicroSecondsI() const;
  long long toMilliSecondsI() const;
  long long toSecondsI() const;
  long long toMinutesI() const;
  long long toHoursI() const;

  double toMicroSecondsF() const;
  double toMilliSecondsF() const;
  double toSecondsF() const;
  double toMinutesF() const;
  double toHoursF() const;

  static constexpr long long kMicrosecondsInMilliseconds = 1'000;
  static constexpr long long kMicrosecondsInSeconds = 1'000'000;
  static constexpr long long kMillisecondsInSeconds = 1'000;
  static constexpr long long kMicrosecondsInMinutes = 60'000'000;
  static constexpr long long kMicrosecondsInHours = 3'600'000'000;

protected:
  CTime(long long microseconds);
  template<class TArchive>
  void serialize(TArchive& arch, const unsigned int) {
    arch& Microseconds_;
  }

  long long Microseconds_ = 0;
};
} // namespace NSApplication

#endif // NSAPPLICATION_CTIMEAPP_H
