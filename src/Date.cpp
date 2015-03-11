#include "Date.hh"

Date::Date(const unsigned int day, const unsigned int month, const unsigned int year)
  : _day(day),
    _month(month),
    _year(year) {
  std::ostringstream ss;
  ss << year << '-' << month << '-' << day;
  _dateAsString = ss.str();
  if (!isValid()) throw -1;
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
  if (!isValid()) throw -1;
}

Date::~Date() {}

const unsigned int &Date::getDay() const {
 return _day;
}

const unsigned int &Date::getMonth() const {
 return _month;
}

const unsigned int &Date::getYear() const {
 return _year;
}

const std::string  &Date::getDateString() const {
 return _dateAsString;
}

bool Date::compareDay(Date *date) const {
  return _day   == date->getDay()
      && _month == date->getMonth()
      && _year  == date->getYear();
}

bool Date::compareMonth(Date *date) const {
  return _month == date->getMonth()
      && _year  == date->getYear();
}

bool Date::isValid() {
  //                        1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12
  _nbrDaysInMonths.assign({31,28,30,31,30,31,30,31,30,31,30,31});
  return (_month && _month <= _nbrDaysInMonths.size())
    && (_day && _day <= _nbrDaysInMonths[_month - 1])
    && _year < 2016;
}

std::ostream &operator<<(std::ostream &os, const Date *date) {
  os  << std::setfill('0')
      << std::setw(2) << date->getDay() << '/'
      << std::setw(2) << date->getMonth() << '/'
      << std::setw(4) << date->getYear()
      << std::setfill(' ');
  return os;
}
