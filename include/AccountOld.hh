#ifndef ACCOUNT_OLD_HH
#define ACCOUNT_OLD_HH

#include "Account.hh"
#include "God.hh"

class AccountOld : public Account {
public:
  AccountOld(User *user, Id *id, double balance, Id *tutor);
  virtual ~AccountOld();
  virtual WithdrawStatus withdraw(const double amount, Date *date);
};

#endif // ACCOUNT_OLD_HH
