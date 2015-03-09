#include "AccountChild.hh"

AccountChild::AccountChild(User *user, Id *id, double balance, Account *tutor)
  : Account(user, id, balance, tutor) {
  _type = CHILD;
  _menuAccount->push_back("Display tutor info", &Account::showListTutor);
}

AccountChild::~AccountChild() {}

double AccountChild::getTotalWithdrawThisDay(Date *date) {
  double sum = 0;
  for (Transaction *t : _listTransactions) {
    if (t->getDate()->compareDay(date))
      sum += t->getAmount();
  }
  return sum;
}

double AccountChild::getTotalWithdrawThisMonth(Date *date) {
  double sum = 0;
  for (Transaction *t : _listTransactions) {
    if (t->getDate()->compareMonth(date))
      sum += t->getAmount();
  }
  return sum;
}

Transaction::Status AccountChild::withdraw(const double amount, Date *date, Transaction::Status status) {
  if (amount > 10 || getTotalWithdrawThisDay(date) > 10)
    status = Transaction::DAY_LIMIT;
  if (getTotalWithdrawThisMonth(date) > 50)
    status = Transaction::MONTH_LIMIT;
  return Account::withdraw(amount, date, status);
}
