#ifndef DATE_HH
#define DATE_HH

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

class Date {
private:
  unsigned int              _day;
  unsigned int              _month;
  unsigned int              _year;
  std::string               _dateAsString;
  std::vector<unsigned int> _nbrDaysInMonths;

  bool isValid();
public:
  Date(const unsigned int, const unsigned int, const unsigned int);
  Date(const std::string &);
  ~Date();

  const unsigned int &getDay()         const;
  const unsigned int &getMonth()       const;
  const unsigned int &getYear()        const;
  const std::string  &getDateString()  const;

  bool compareDay(Date *) const;
  bool compareMonth(Date *) const;
};

std::ostream &operator<<(std::ostream &, const Date *);

#endif // DATE_HH
