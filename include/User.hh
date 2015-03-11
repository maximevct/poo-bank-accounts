#ifndef USER_HH
#define USER_HH

#include "Date.hh"

class User {
private:
  std::string _firstName;
  std::string _lastName;
  Date        *_birthdate;
public:
  User(const std::string &, const std::string &, Date *);
  ~User();

  const std::string &getFirstName() const;
  const std::string &getLastName()  const;
  const Date *getBirthdate()        const;
};

std::ostream &operator<<(std::ostream &, const User *);

#endif // USER_HH
