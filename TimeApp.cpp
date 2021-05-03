#include "TimeApp.h"

namespace NSApplication {

CTime operator+(const CTime& first, const CTime& second) {
  return CTime(first.Microseconds_ + second.Microseconds_);
}

CTime operator-(const CTime& first, const CTime& second) {
  return CTime(first.Microseconds_ - second.Microseconds_);
}

CTime& CTime::operator+=(const CTime& other) {
  Microseconds_ += other.Microseconds_;
  return *this;
}

CTime& CTime::operator-=(const CTime& other) {
  Microseconds_ -= other.Microseconds_;
  return *this;
}

bool operator<(const CTime& first, const CTime& second) {
  return first.Microseconds_ < second.Microseconds_;
}

bool operator>(const CTime& first, const CTime& second) {
  return second < first;
}

bool operator<=(const CTime& first, const CTime& second) {
  return !(second < first);
}

bool operator>=(const CTime& first, const CTime& second) {
  return !(first < second);
}

bool operator==(const CTime& first, const CTime& second) {
  return first.Microseconds_ == second.Microseconds_;
}

bool operator!=(const CTime& first, const CTime& second) {
  return !(first == second);
}

CTime CTime::operator-() const {
  return CTime(-Microseconds_);
}

long long CTime::toMicroSecondsI() const {
  return Microseconds_;
}

long long CTime::toMilliSecondsI() const {
  return Microseconds_ / kMicrosecondsInMilliseconds;
}

long long CTime::toSecondsI() const {
  return Microseconds_ / kMicrosecondsInSeconds;
}

double CTime::toMicroSecondsF() const {
  return static_cast<double>(Microseconds_);
}

double CTime::toMilliSecondsF() const {
  return Microseconds_ / static_cast<double>(kMicrosecondsInMilliseconds);
}

double CTime::toSecondsF() const {
  return Microseconds_ / static_cast<double>(kMicrosecondsInSeconds);
}

CTime::CTime(long long microseconds) : Microseconds_(microseconds) {
}

MicroSeconds::MicroSeconds(long long microseconds) : CTime(microseconds) {
}

MilliSeconds::MilliSeconds(long long milliseconds)
    : CTime(kMicrosecondsInMilliseconds * milliseconds) {
}

Seconds::Seconds(long long seconds) : CTime(kMicrosecondsInSeconds * seconds) {
}

} // namespace NSApplication
