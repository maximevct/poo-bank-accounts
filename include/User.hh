#ifndef USER_HH
#define USER_HH

#include "Date.hh"

class User {
private:
  std::string _firstName;
  std::string _lastName;
  Date        *_birthdate;
public:
  User(const std::string &firstName, const std::string &lastName, Date *date);
  User(const User &user);
  ~User();

  const std::string &getFirstName() const;
  const std::string &getLastName()  const;
  Date *getBirthdate()              const;
};


#endif // USER_HH