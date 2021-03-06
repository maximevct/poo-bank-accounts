#ifndef LIST_ACCOUNTS_HH
#define LIST_ACCOUNTS_HH

#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <map>

#include "AccountFactory.hh"
#include "Menu.hh"
#include "User.hh"
#include "Date.hh"
#include "Id.hh"

class ListAccounts {
private:
  enum elemType { ACCOUNT_ID, ACCOUNT_TYPE, USER_LASTNAME, USER_FIRSTNAME, USER_BIRTHDATE, ACCOUNT_TUTOR_ID, BALANCE, TRANSACTIONS };
  std::string                     _filename;
  std::list<Account *>            _listAccounts;
  std::map<Id *, Id *>            _listAccountsUnlinked;
  AccountFactory                  _accountFactory;
  Menu<void, ListAccounts>        *_menuListAccounts;
  std::map<elemType, std::string> _listElemTypes;

  Account::AccountType askForType(const std::string &);
  Date                 *askForDate(const std::string &);
  Id                   *askForId(const std::string &);
  const std::string    askForString(const std::string &);
  User                 *askForUser();
  void                 createFromALineCSV(const std::string &);
  void                 setElemTypes();
  void                 deleteById(Id *);
  void                 emptyListMsg();
public:
  ListAccounts(const std::string &);
  ListAccounts();
  ~ListAccounts();

  void load();
  void save();
  void menu();

  void displayListAccounts();
  void selectAnAccount();
  void addAnAccount();
  void deleteAnAccount();

  Account *getById(Id *);
};

#endif // LIST_ACCOUNTS_HH
