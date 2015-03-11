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
  std::map<Account::AccountType, Account *(AccountFactory::*)(User *, Id *, double, Account *)> _listAccountTypes;

  Account *createAccountNormal(User *, Id *, double, Account *);
  Account *createAccountChild(User *, Id *, double, Account *);
  Account *createAccountOld(User *, Id *, double, Account *);
public:
  AccountFactory();
  ~AccountFactory();
  Account *createAccount(Account::AccountType, User *, Id *, double = 0, Account * = NULL);
};


#endif // ACCOUNT_FACTORY_HH
