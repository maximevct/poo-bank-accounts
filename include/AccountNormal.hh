#ifndef ACCOUNT_NORMAL_HH
#define ACCOUNT_NORMAL_HH

#include "Account.hh"

class AccountNormal : public Account {
public:
  AccountNormal(User *user, Id *id, double balance, Id *tutor);
  virtual ~AccountNormal();
};

#endif // ACCOUNT_NORMAL_HH
