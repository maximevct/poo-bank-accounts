#ifndef ACCOUNT_FACTORY_HH
#define ACCOUNT_FACTORY_HH

#include <map>

#include "Account.hh"
#include "AccountNormal.hh"
#include "AccountChild.hh"
#include "AccountOld.hh"
#include "User.hh"
#include "Id.hh"

class AccountFactory {
private:
  std::map<Account::AccountType, Account *(AccountFactory::*)(User *, Id *, double, Id *)> _listAccountTypes;

  Account *createAccountNormal(User *user, Id *id, double balance, Id *tutor);
  Account *createAccountChild(User *user, Id *id, double balance, Id *tutor);
  Account *createAccountOld(User *user, Id *id, double balance, Id *tutor);
public:
  AccountFactory();
  ~AccountFactory();
  Account *createAccount(Account::AccountType type, User *user, Id *id, double balance = 0, Id *tutor = NULL);
};


#endif // ACCOUNT_FACTORY_HH
