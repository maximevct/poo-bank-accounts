#include "Account.hh"

double Account::getTotalWithdrawThisDay(Date *date) {
  double sum = 0;
  for (Transaction *t : _listTransactions) {
    if (t->getDate()->compareDay(date))
      sum += t->getAmount();
  }
  return sum;
}

double Account::getTotalWithdrawThisMonth(Date *date) {
  double sum = 0;
  for (Transaction *t : _listTransactions) {
    if (t->getDate()->compareMonth(date))
      sum += t->getAmount();
  }
  return sum;
}

Account::Account(User *user, Id *id, double balance, Id *tutor) {
  _user              = user;
  _balance           = balance;
  IdGenerator *idGen = IdGenerator::getInstance();
  _tutor             = tutor;
  _id                = (id == NULL) ? idGen->generateId(user) : idGen->useId(id);
}

const Id                       *Account::getId()           const { return _id; }
const User                     *Account::getUser()         const { return _user; }
const Id                       *Account::getTutor()        const { return _tutor; }
const std::list<Transaction *> &Account::getTransactions() const { return _listTransactions; }
double                          Account::getBalance()      const { return _balance; }
Account::AccountType            Account::getType()         const { return _type; }

Account::WithdrawStatus Account::withdraw(const double amount, Date *date) {
  if (_balance > amount) {
    _balance -= amount;
    _listTransactions.push_back(new Transaction(amount, date));
    return Account::SUCCESS;
  }
  return Account::INSUF_BALANCE;
}

void Account::addTransaction(const double amount, Date *date) {
  _listTransactions.push_back(new Transaction(amount, date));
}

Account::~Account() {}
