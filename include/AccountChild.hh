#ifndef ACCOUNT_CHILD_HH
#define ACCOUNT_CHILD_HH

#include "Account.hh"

class AccountChild : public Account {
private:
  double getTotalWithdrawThisDay(Date *);
  double getTotalWithdrawThisMonth(Date *);
public:
  AccountChild(User *, Id *, double, Account *);
  virtual ~AccountChild();

  virtual Transaction::Status withdraw(const double, Date *, Transaction::Status = Transaction::SUCCESS);
};

#endif // ACCOUNT_CHILD_HH
