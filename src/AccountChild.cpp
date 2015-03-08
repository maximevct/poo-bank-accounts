#include "AccountChild.hh"

AccountChild::AccountChild(User *user, Id *id, double balance, Id *tutor)
  : Account(user, id, balance, tutor) {
  _type = CHILD;
}

AccountChild::~AccountChild() {}

AccountChild::TransactionStatus AccountChild::withdraw(const double amount, Date *date) {
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
