#include "AccountFactory.hh"

Account *AccountFactory::createAccountNormal(User *user, Id *id, double balance, Id *tutor) {
  return new AccountNormal(user, id, balance, tutor);
}

Account *AccountFactory::createAccountChild(User *user, Id *id, double balance, Id *tutor) {
  return new AccountChild(user, id, balance, tutor);
}

Account *AccountFactory::createAccountOld(User *user, Id *id, double balance, Id *tutor) {
  return new AccountOld(user, id, balance, tutor);
}

AccountFactory::AccountFactory() {
  _listAccountTypes[Account::NORMAL] = &AccountFactory::createAccountNormal;
  _listAccountTypes[Account::CHILD]  = &AccountFactory::createAccountChild;
  _listAccountTypes[Account::OLD]    = &AccountFactory::createAccountOld;
}

Account *AccountFactory::createAccount(Account::AccountType type, User *user, Id *id, double balance, Id *tutor) {
  return (this->*_listAccountTypes[type])(user, id, balance, tutor);
}

AccountFactory::~AccountFactory() {}
