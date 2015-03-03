#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

class Date {
private:
  unsigned int _day;
  unsigned int _month;
  unsigned int _year;
  std::string  _dateAsString;
public:
  Date(const unsigned int day, const unsigned int month, const unsigned int year)
    : _day(day),
      _month(month),
      _year(year) {
    std::ostringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << day
       << std::setw(2) << month
       << std::setw(4) << year;
    _dateAsString = ss.str();
  }

  Date(const Date &date)
    : _day(date.getDay()),
      _month(date.getMonth()),
      _year(date.getYear()),
      _dateAsString(date.getDateString()) {}

  Date &operator=(const Date &date) {
    if (this != &date) {
      _day = date.getDay();
      _month = date.getMonth();
      _year = date.getYear();
      _dateAsString = date.getDateString();
    }
    return *this;
  }

  ~Date() {}

  const unsigned int &getDay()         const { return _day;          }
  const unsigned int &getMonth()       const { return _month;        }
  const unsigned int &getYear()        const { return _year;         }
  const std::string  &getDateString()  const { return _dateAsString; }
};

std::ostream &operator<<(std::ostream &os, const Date &date) {
  os  << std::setfill('0')
      << std::setw(2) << date.getDay() << '/'
      << std::setw(2) << date.getMonth() << '/'
      << std::setw(4) << date.getYear();
  return os;
}

class User {
private:
  std::string _firstName;
  std::string _lastName;
  Date        _birthdate;
  User        *_tutor;
public:
  User(const std::string &firstName, const std::string &lastName, const Date &date)
    : _firstName(firstName),
      _lastName(lastName),
      _birthdate(date) {
    _tutor = NULL;
  }

  User(const User &user)
    : _firstName(user.getFirstName()),
      _lastName(user.getLastName()),
      _birthdate(user.getDate()) {
    _tutor = user.getTutor();
  }

  ~User() {}

  const std::string &getFirstName() const { return _firstName;  }
  const std::string &getLastName()  const { return _lastName;   }
  const Date &getDate()             const { return _birthdate;  }
  User *getTutor()            const { return _tutor;      }
  void setTutor(User *tutor) { _tutor = tutor; }
};

std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "Firstname : " << user.getFirstName() << "\n"
     << "Lastname  : " << user.getLastName() << "\n"
     << "Birthdate : " << user.getDate();
  return os;
}

class Id {
private:
  const std::string _id;
public:
  Id(const std::string id) : _id(id) {}

  ~Id() {}

  const std::string &getId() const { return _id; }
  bool operator==(const Id &id) {
    return getId() == id.getId();
  }
};

std::ostream &operator<<(std::ostream &os, const Id *id) {
  os << id->getId();
  return os;
}

class IdGenerator {
private:
  static IdGenerator *_instance;
  std::list<Id> _listIds;

  IdGenerator() {}

  bool  issetId(const std::string &id) {
    std::list<Id>::iterator it;
    it = find(_listIds.begin(), _listIds.end(), id);
    return it != _listIds.end();
  }

  Id *createNewId(const std::string &id) {
    Id *newId = new Id(id);
    _listIds.push_back(id);
    return newId;
  }

public:
  static IdGenerator *getInstance() {
    if (_instance == NULL) {
      _instance = new IdGenerator();
    }
    return _instance;
  }

  ~IdGenerator() {}

  Id *generateId(User *user, const int i = 1) {
    std::string idAsString;
    idAsString = user->getFirstName() + user->getLastName() + user->getDate().getDateString() + std::to_string(i);
    return (issetId(idAsString)) ? generateId(user, i + 1) : createNewId(idAsString);
  }
};

IdGenerator *IdGenerator::_instance = NULL;

class Transaction {
private:
  int   _amount;
  Date  _date;
public:
  Transaction(int amount, const Date &date)
    : _amount(amount),
      _date(date) {}
};

class Account {
protected:
  User  *_user;
  Id    *_id;
  int   _balance;
  std::list<Transaction *> _listTransactions;

public:
  Account(User *user) {
    _balance = 0;
    _id = IdGenerator::getInstance()->generateId(user);
  }

  virtual bool withdraw(const int amount, const Date &date) {
    if (_balance > amount) {
      _balance -= amount;
      _listTransactions.push_back(new Transaction(amount, date));
      return true;
    }
    return false;
  }

  virtual ~Account() {}
};

class AccountNormal : public Account {
public:
  AccountNormal(User *user) : Account(user) {}
  virtual ~AccountNormal() {};
};

class AccountChild : public Account {
public:
  AccountChild(User *user) : Account(user) {}
  virtual ~AccountChild() {};
};

class AccountOld : public Account {
public:
  AccountOld(User *user) : Account(user) {}
  virtual ~AccountOld() {};
};

class AccountFactory {
private:
  enum AccountType { NORMAL, CHILD, OLD };
  static std::vector<Account *(AccountFactory::*)(User *)> _listAccountTypes;
  Account *createAccountNormal(User *user) {
    return new AccountNormal(user);
  }
  Account *createAccountChild(User *user) {
    return new AccountChild(user);
  }
  Account *createAccountOld(User *user) {
    return new AccountOld(user);
  }
public:
  AccountFactory() {
    _listAccountTypes[NORMAL] = &AccountFactory::createAccountNormal;
    _listAccountTypes[CHILD]  = &AccountFactory::createAccountChild;
    _listAccountTypes[OLD]    = &AccountFactory::createAccountOld;
  }

  Account *createAccount(User *user, AccountType type) {
    return (this->*_listAccountTypes[type])(user);
  }

  ~AccountFactory() {}
};

class ListAccounts {
private:
  std::list<Account *> _listAccounts;
  std::string _filename;

public:
  ListAccounts(const std::string &filename) : _filename(filename) {}
  ~ListAccounts() {}

  std::list<Account *>  &load() {
    std::ifstream file(_filename);

    while (file) {
      std::string line;
      getline(file, line);

    }
    return _listAccounts;
  }
};

int     main(int ac, char *av[]) {
  ListAccounts    listAccounts(av[1]);

  listAccounts.load();
  return 0;
}
