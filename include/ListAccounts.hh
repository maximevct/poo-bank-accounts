#ifndef LIST_ACCOUNTS_HH
#define LIST_ACCOUNTS_HH

#include <iostream>
#include <fstream>

#include "AccountFactory.hh"
#include "Menu.hh"

class ListAccounts {
private:
  std::string          _filename;
  std::list<Account *> _listAccounts;
  AccountFactory       _accountFactory;
  Menu<void, ListAccounts> *_menuListAccounts;
  enum elemType { USER_ID, ACCOUNT_TYPE, USER_LASTNAME, USER_FIRSTNAME, USER_BIRTHDATE, ACCOUNT_TUTOR_ID, BALANCE, TRANSACTIONS };

  void  createFromALineCSV(const std::string &line);
public:
  ListAccounts(const std::string &filename);
  ~ListAccounts();

  void load();
  void save();
  void menu();

  void displayListAccounts();
  void selectAnAccount();
  void addAnAccount();
};

#endif // LIST_ACCOUNTS_HH
