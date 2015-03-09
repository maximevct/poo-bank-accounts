#include "AccountOld.hh"

AccountOld::AccountOld(User *user, Id *id, double balance, Account *tutor) : Account(user, id, balance, tutor) {
  _type = OLD;
}

AccountOld::~AccountOld() {};

Transaction::Status AccountOld::withdraw(const double amount, Date *date, Transaction::Status status) {
  if (!God::doYouAuthorizeThisMyLord()) {
    status = Transaction::UNAUTHORIZED;
  }
  return Account::withdraw(amount, date, status);
}
