#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>

class God {
public:
  // Calculus to emulate God reflexion when someone wants something
  // Pretty accurate but not very sure he really use this way...
  static bool doYouAuthorizeThisMyLord() {
    int imAFeelingGoodToday = rand() % 2;
    int repeatMeThatIAmTheBestUntilITellYouToStop = rand() % 10;
    int justKiddingButTellMeAgain = rand() % 42 + 12;
    int doItAgainMotherFu = 0;
    while (repeatMeThatIAmTheBestUntilITellYouToStop != 7) {
      doItAgainMotherFu++;
      repeatMeThatIAmTheBestUntilITellYouToStop = rand() % 10;
    }
    justKiddingButTellMeAgain /= doItAgainMotherFu + 1;
    return imAFeelingGoodToday == (justKiddingButTellMeAgain > repeatMeThatIAmTheBestUntilITellYouToStop);
  }
};

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
    ss << year << '-' << month << '-' << day;
    _dateAsString = ss.str();
  }

  Date(const std::string &dateAsString)
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

  bool compareDay(Date *date) const {
    return _day   == date->getDay()
        && _month == date->getMonth()
        && _year  == date->getYear();
  }

  bool compareMonth(Date *date) const {
    return _month == date->getMonth()
        && _year  == date->getYear();
  }
};

std::ostream &operator<<(std::ostream &os, Date *date) {
  os  << std::setfill('0')
      << std::setw(2) << date->getDay() << '/'
      << std::setw(2) << date->getMonth() << '/'
      << std::setw(4) << date->getYear();
  return os;
}

class User {
private:
  std::string _firstName;
  std::string _lastName;
  Date        *_birthdate;
public:
  User(const std::string &firstName, const std::string &lastName, Date *date)
    : _firstName(firstName),
      _lastName(lastName) {
    _birthdate = date;
  }

  User(const User &user)
    : _firstName(user.getFirstName()),
      _lastName(user.getLastName()) {
    _birthdate = user.getBirthdate();
  }

  ~User() {}

  const std::string &getFirstName() const { return _firstName;  }
  const std::string &getLastName()  const { return _lastName;   }
  Date *getBirthdate()              const { return _birthdate;  }
};

std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "Firstname : " << user.getFirstName() << "\n"
     << "Lastname  : " << user.getLastName() << "\n"
     << "Birthdate : " << user.getBirthdate();
  return os;
}

class Id {
private:
  const std::string _id;
public:
  Id(const std::string &id) : _id(id) {}
  ~Id() {}

  const std::string &getId() const { return _id; }

  bool operator==(Id *id) {
    return getId() == id->getId();
  }

  bool operator==(const std::string &id) {
    return getId() == id;
  }
};

bool operator==(Id* idObj, const std::string &idStr) {
  return idObj->getId() == idStr;
}

std::ostream &operator<<(std::ostream &os, const Id *id) {
  os << id->getId();
  return os;
}

class IdGenerator {
private:
  static IdGenerator *_instance;
  std::list<Id *>     _listIds;

  IdGenerator() {}

  bool  issetId(const std::string &id) {
    std::list<Id *>::iterator it;
    it = find(_listIds.begin(), _listIds.end(), id);
    return it != _listIds.end();
  }

  Id *createNewId(const std::string &id) {
    Id *newId = new Id(id);
    _listIds.push_back(newId);
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

  Id *useId(Id *id) {
    _listIds.push_back(id);
    return id;
  }

  Id *generateId(User *user, const int i = 1) {
    std::string idAsString;
    idAsString = user->getFirstName() + user->getLastName() + user->getBirthdate()->getDateString() + std::to_string(i);
    return (issetId(idAsString)) ? generateId(user, i + 1) : createNewId(idAsString);
  }
};

IdGenerator *IdGenerator::_instance = NULL;

class Transaction {
private:
  double _amount;
  Date  *_date;
public:
  Transaction(double amount, Date *date)
    : _amount(amount) {
      _date = date;
    }

  double getAmount() const { return _amount; }
  Date *getDate() const { return _date; }
};

class Account {
public:
  enum AccountType    { NORMAL = 'R', CHILD = 'E', OLD = 'A' };
  enum WithdrawStatus { SUCCESS, INSUF_BALANCE, DAY_LIMIT, MONTH_LIMIT, UNAUTHORIZED };
protected:
  User                    *_user;
  Id                      *_id;
  Id                      *_tutor;
  double                   _balance;
  Account::AccountType     _type;
  std::list<Transaction *> _listTransactions;

  double getTotalWithdrawThisDay(Date *date) {
    double sum = 0;
    for (Transaction *t : _listTransactions) {
      if (t->getDate()->compareDay(date))
        sum += t->getAmount();
    }
    return sum;
  }

  double getTotalWithdrawThisMonth(Date *date) {
    double sum = 0;
    for (Transaction *t : _listTransactions) {
      if (t->getDate()->compareMonth(date))
        sum += t->getAmount();
    }
    return sum;
  }
public:
  Account(User *user, Id *id, double balance, Id *tutor) {
    _user              = user;
    _balance           = balance;
    IdGenerator *idGen = IdGenerator::getInstance();
    _tutor             = tutor;
    _id                = (id == NULL) ? idGen->generateId(user) : idGen->useId(id);
  }

  const Id                       *getId()           const { return _id; }
  const User                     *getUser()         const { return _user; }
  const Id                       *getTutor()        const { return _tutor; }
  const std::list<Transaction *> &getTransactions() const { return _listTransactions; }
  double                          getBalance()      const { return _balance; }
  AccountType                     getType()         const { return _type; }

  virtual WithdrawStatus withdraw(const double amount, Date *date) {
    if (_balance > amount) {
      _balance -= amount;
      _listTransactions.push_back(new Transaction(amount, date));
      return SUCCESS;
    }
    return INSUF_BALANCE;
  }

  virtual void addTransaction(const double amount, Date *date) {
    _listTransactions.push_back(new Transaction(amount, date));
  }

  virtual ~Account() {}
};

class AccountNormal : public Account {
public:
  AccountNormal(User *user, Id *id, double balance, Id *tutor) : Account(user, id, balance, tutor) {
    _type = NORMAL;
  }
  virtual ~AccountNormal() {};
};

class AccountChild : public Account {
public:
  AccountChild(User *user, Id *id, double balance, Id *tutor) : Account(user, id, balance, tutor) {
    _type = CHILD;
  }
  virtual ~AccountChild() {};

  virtual WithdrawStatus withdraw(const double amount, Date *date) {
    if (getTotalWithdrawThisDay(date) > 10) {
      return DAY_LIMIT;
    }
    if (getTotalWithdrawThisMonth(date) > 50) {
      return MONTH_LIMIT;
    }
    if (_balance > amount) {
      _balance -= amount;
      _listTransactions.push_back(new Transaction(amount, date));
      return SUCCESS;
    }
    return INSUF_BALANCE;
  }
};

class AccountOld : public Account {
public:
  AccountOld(User *user, Id *id, double balance, Id *tutor) : Account(user, id, balance, tutor) {
    _type = OLD;
  }
  virtual ~AccountOld() {};

  virtual WithdrawStatus withdraw(const double amount, Date *date) {
    if (!God::doYouAuthorizeThisMyLord()) {
      return UNAUTHORIZED;
    }
    if (_balance > amount) {
      _balance -= amount;
      _listTransactions.push_back(new Transaction(amount, date));
      return SUCCESS;
    }
    return INSUF_BALANCE;
  }
};

class AccountFactory {
private:
  std::vector<Account *(AccountFactory::*)(User *, Id *, double, Id *)> _listAccountTypes;

  Account *createAccountNormal(User *user, Id *id, double balance, Id *tutor) {
    return new AccountNormal(user, id, balance, tutor);
  }

  Account *createAccountChild(User *user, Id *id, double balance, Id *tutor) {
    return new AccountChild(user, id, balance, tutor);
  }

  Account *createAccountOld(User *user, Id *id, double balance, Id *tutor) {
    return new AccountOld(user, id, balance, tutor);
  }
public:
  AccountFactory() {
    _listAccountTypes.resize(3);
    _listAccountTypes[Account::NORMAL] = &AccountFactory::createAccountNormal;
    _listAccountTypes[Account::CHILD]  = &AccountFactory::createAccountChild;
    _listAccountTypes[Account::OLD]    = &AccountFactory::createAccountOld;
  }

  Account *createAccount(Account::AccountType type, User *user, Id *id, double balance = 0, Id *tutor = NULL) {
    return (this->*_listAccountTypes[type])(user, id, balance, tutor);
  }

  ~AccountFactory() {}
};

class ListAccounts {
private:
  std::string          _filename;
  std::list<Account *> _listAccounts;
  AccountFactory       _accountFactory;
  enum elemType { USER_ID, ACCOUNT_TYPE, USER_LASTNAME, USER_FIRSTNAME, USER_BIRTHDATE, ACCOUNT_TUTOR_ID, BALANCE, TRANSACTIONS };

  void  createFromALineCSV(const std::string &line) {
    std::stringstream          lineStream(line);
    std::vector<std::string>  _listElems(TRANSACTIONS);

    for (int i = 0; lineStream && i < TRANSACTIONS; i++) {
      std::getline(lineStream, _listElems[i], ',');
    }
    Account *newAccount = _accountFactory.createAccount(
      static_cast<Account::AccountType>(_listElems[ACCOUNT_TYPE][0]),
      new User(_listElems[USER_FIRSTNAME],
        _listElems[USER_LASTNAME],
        new Date(_listElems[USER_BIRTHDATE])),
      new Id(_listElems[USER_ID]),
      std::stod(_listElems[BALANCE]),
      (_listElems[ACCOUNT_TUTOR_ID].length() ? (new Id(_listElems[ACCOUNT_TUTOR_ID])) : NULL)
    );

    std::string transactionAmount;
    std::string transactionDate;
    while (lineStream) {
      std::getline(lineStream, transactionDate, ',');
      std::getline(lineStream, transactionAmount, ',');
      if (lineStream) {
        newAccount->addTransaction(std::stod(transactionAmount), new Date(transactionDate));
      }
    }
    _listAccounts.push_back(newAccount);
  }

public:
  ListAccounts(const std::string &filename) : _filename(filename) {}
  ~ListAccounts() {}

  void  load() {
    std::ifstream file(_filename);
    if (file) {
      while (file) {
        std::string line;
        if (getline(file, line))
          createFromALineCSV(line);
      }
    }
    else {
      std::cerr << "Error : Cannot load file : " << _filename << std::endl;
    }
  }

  void save() {
    std::ofstream file(_filename, std::ios::trunc);
    if (file) {
      for (Account *a : _listAccounts) {
        file << a->getId()->getId()                           << ','
             << static_cast<char>(a->getType())               << ','
             << a->getUser()->getLastName()                   << ','
             << a->getUser()->getFirstName()                  << ','
             << a->getUser()->getBirthdate()->getDateString() << ','
             << (a->getTutor() ? a->getTutor()->getId() : "") << ','
             << std::fixed << std::setprecision(2) << a->getBalance();
        for (Transaction *t : a->getTransactions()) {
          file << ',' << t->getDate()->getDateString()
               << ',' << t->getAmount();
        }
        file << std::endl;
      }
    }
  }
};

int     main(int ac, char *av[]) {
  if (ac == 2) {
    ListAccounts    listAccounts(av[1]);
    listAccounts.load();
    listAccounts.save();
  }

  return 0;
}
