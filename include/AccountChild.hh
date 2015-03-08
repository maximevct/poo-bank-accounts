#ifndef ACCOUNT_CHILD_HH
#define ACCOUNT_CHILD_HH

#include "Account.hh"

class AccountChild : public Account {
public:
  AccountChild(User *user, Id *id, double balance, Id *tutor);
  virtual ~AccountChild();

  virtual TransactionStatus withdraw(const double amount, Date *date);
};

#endif // ACCOUNT_CHILD_HH
