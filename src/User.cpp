#include "User.hh"

User::User(const std::string &firstName, const std::string &lastName, Date *date)
  : _firstName(firstName),
    _lastName(lastName) {
  _birthdate = date;
}

User::User(const User &user)
  : _firstName(user.getFirstName()),
    _lastName(user.getLastName()) {
  _birthdate = user.getBirthdate();
}

User::~User() {}

const std::string &User::getFirstName() const { return _firstName;  }
const std::string &User::getLastName()  const { return _lastName;   }
Date *User::getBirthdate()              const { return _birthdate;  }

std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "Firstname : " << user.getFirstName() << "\n"
     << "Lastname  : " << user.getLastName() << "\n"
     << "Birthdate : " << user.getBirthdate();
  return os;
}
