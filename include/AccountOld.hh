#ifndef ACCOUNT_OLD_HH
#define ACCOUNT_OLD_HH

#include "Account.hh"
#include "God.hh"

class AccountOld : public Account {
public:
  AccountOld(User *, Id *, double, Account *);
  virtual ~AccountOld();
  virtual Transaction::Status withdraw(const double, Date *, Transaction::Status = Transaction::SUCCESS);
};

#endif // ACCOUNT_OLD_HH
