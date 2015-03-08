#include "Date.hh"

Date::Date(const unsigned int day, const unsigned int month, const unsigned int year)
  : _day(day),
    _month(month),
    _year(year) {
  std::ostringstream ss;
  ss << year << '-' << month << '-' << day;
  _dateAsString = ss.str();
}

Date::Date(const std::string &dateAsString)
  : _dateAsString(dateAsString) {
  std::stringstream          lineStream(_dateAsString);
  std::string                year;
  std::string                month;
  std::string                day;

  std::getline(lineStream, year,  '-');
  std::getline(lineStream, month, '-');
  std::getline(lineStream, day,   '-');
  _day   = std::stoi(day);
  _month = std::stoi(month);
  _year  = std::stoi(year);
}

Date::Date(const Date &date)
  : _day(date.getDay()),
    _month(date.getMonth()),
    _year(date.getYear()),
    _dateAsString(date.getDateString()) {}

Date &Date::operator=(const Date &date) {
  if (this != &date) {
    _day = date.getDay();
    _month = date.getMonth();
    _year = date.getYear();
    _dateAsString = date.getDateString();
  }
  return *this;
}

Date::~Date() {}

const unsigned int &Date::getDay()         const { return _day;          }
const unsigned int &Date::getMonth()       const { return _month;        }
const unsigned int &Date::getYear()        const { return _year;         }
const std::string  &Date::getDateString()  const { return _dateAsString; }

bool Date::compareDay(Date *date) const {
  return _day   == date->getDay()
      && _month == date->getMonth()
      && _year  == date->getYear();
}

bool Date::compareMonth(Date *date) const {
  return _month == date->getMonth()
      && _year  == date->getYear();
}

std::ostream &operator<<(std::ostream &os, const Date *date) {
  os  << std::setfill('0')
      << std::setw(2) << date->getDay() << '/'
      << std::setw(2) << date->getMonth() << '/'
      << std::setw(4) << date->getYear()
      << std::setfill(' ');
  return os;
}
