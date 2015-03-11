#ifndef ACCOUNT_NORMAL_HH
#define ACCOUNT_NORMAL_HH

#include "Account.hh"

class AccountNormal : public Account {
public:
  AccountNormal(User *, Id *, double, Account *);
  virtual ~AccountNormal();
};

#endif // ACCOUNT_NORMAL_HH
