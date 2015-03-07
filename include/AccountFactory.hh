#ifndef ACCOUNT_FACTORY_HH
#define ACCOUNT_FACTORY_HH

#include <vector>

#include "Account.hh"
#include "AccountNormal.hh"
#include "AccountChild.hh"
#include "AccountOld.hh"
#include "User.hh"
#include "Id.hh"

class AccountFactory {
private:
  std::vector<Account *(AccountFactory::*)(User *, Id *, double, Id *)> _listAccountTypes;

  Account *createAccountNormal(User *user, Id *id, double balance, Id *tutor);
  Account *createAccountChild(User *user, Id *id, double balance, Id *tutor);
  Account *createAccountOld(User *user, Id *id, double balance, Id *tutor);
public:
  AccountFactory();
  Account *createAccount(Account::AccountType type, User *user, Id *id, double balance = 0, Id *tutor = NULL);
  ~AccountFactory();
};


#endif // ACCOUNT_FACTORY_HH
