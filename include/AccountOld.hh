#ifndef ACCOUNT_OLD_HH
#define ACCOUNT_OLD_HH

#include "Account.hh"
#include "God.hh"

class AccountOld : public Account {
public:
  AccountOld(User *user, Id *id, double balance, Account *tutor);
  virtual ~AccountOld();
  virtual Transaction::Status withdraw(const double amount, Date *date, Transaction::Status = Transaction::SUCCESS);
};

#endif // ACCOUNT_OLD_HH
