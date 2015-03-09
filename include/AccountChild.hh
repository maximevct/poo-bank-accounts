#ifndef ACCOUNT_CHILD_HH
#define ACCOUNT_CHILD_HH

#include "Account.hh"

class AccountChild : public Account {
private:
  double getTotalWithdrawThisDay(Date *date);
  double getTotalWithdrawThisMonth(Date *date);
public:
  AccountChild(User *user, Id *id, double balance, Account *tutor);
  virtual ~AccountChild();

  virtual Transaction::Status withdraw(const double amount, Date *date, Transaction::Status = Transaction::SUCCESS);
};

#endif // ACCOUNT_CHILD_HH
