#include "AccountOld.hh"

AccountOld::AccountOld(User *user, Id *id, double balance, Id *tutor) : Account(user, id, balance, tutor) {
  _type = OLD;
}

AccountOld::~AccountOld() {};

AccountOld::TransactionStatus AccountOld::withdraw(const double amount, Date *date) {
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
