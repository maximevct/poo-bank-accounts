#include "ListAccounts.hh"

ListAccounts::ListAccounts(const std::string &filename)
  : _filename(filename) {
  setElemTypes();
  _menuListAccounts = new Menu<void, ListAccounts>(this, "Main Menu");
  _menuListAccounts->push_back("Display account list", &ListAccounts::displayListAccounts);
  _menuListAccounts->push_back("Select an account"   , &ListAccounts::selectAnAccount);
  _menuListAccounts->push_back("Add an account"      , &ListAccounts::addAnAccount);
  _menuListAccounts->push_back("Delete an account"   , &ListAccounts::deleteAnAccount);
}

ListAccounts::ListAccounts() {
  setElemTypes();
  _menuListAccounts = new Menu<void, ListAccounts>(this, "Main Menu");
  _menuListAccounts->push_back("Display account list", &ListAccounts::displayListAccounts);
  _menuListAccounts->push_back("Select an account"   , &ListAccounts::selectAnAccount);
  _menuListAccounts->push_back("Add an account"      , &ListAccounts::addAnAccount);
  _menuListAccounts->push_back("Delete an account"   , &ListAccounts::deleteAnAccount);
}

ListAccounts::~ListAccounts() {
  delete _menuListAccounts;
}

void ListAccounts::emptyListMsg() {
  std::cout << "Account list is empty, try to add a new one" << std::endl;
}

void ListAccounts::displayListAccounts() {
  if (_listAccounts.size() == 0) {
    emptyListMsg();
    return ;
  }
  std::cout << "List of all accounts :" << std::endl;
  for (Account *a : _listAccounts) {
    std::cout << a << std::endl;
    std::cout << std::setfill('=') << std::setw(70) << "" << std::setfill(' ') << std::endl;
  }
}

Account *ListAccounts::getById(Id *id) {
  for (Account *a : _listAccounts)
    if (a->getId()->getId() == id->getId())
      return a;
  return NULL;
}

void ListAccounts::selectAnAccount() {
  if (_listAccounts.size() == 0) {
    emptyListMsg();
    return ;
  }
  std::string id;
  while (id != "0") {
    std::cout << "Enter the ID account (0 to quit): ";
    std::getline(std::cin, id);
    Account *selected = getById(new Id(id));
    if (selected) {
      std::cout << selected << std::endl;
      selected->menu();
      return;
    }
    else if (id != "0") {
      std::cout << "This account does not exists, try again" << std::endl;
    }
  }
}

void ListAccounts::deleteById(Id *id) {
  std::list<Account *>::iterator it = _listAccounts.begin();
  for (;it != _listAccounts.end() && (*it)->getId()->getId() != id->getId(); ++it);  if (it != _listAccounts.end()) {
    bool issetParent = false;
    for (auto a : _listAccounts)
      if (a->getTutor() != NULL && a->getTutor()->getId() == id->getId()) {
        issetParent = true;
        std::cout << "Cannot delete account, linked to [" << a->getId() << "]" << std::endl;
      }
    if (!issetParent) {
      _listAccounts.erase(it);
      std::cout << "Account succesfully deleted" << std::endl;
    }
  }
}

void ListAccounts::deleteAnAccount() {
  if (_listAccounts.size() == 0) {
    emptyListMsg();
    return ;
  }
  std::string id;
  while (id != "0") {
    std::cout << "Enter the ID account (0 to quit): ";
    std::getline(std::cin, id);
    Account *selected = getById(new Id(id));
    if (selected) {
      deleteById(selected->getId());
      return ;
    }
    else if (id != "0")
      std::cout << "This account does not exists, try again" << std::endl;
  }
}

Date *ListAccounts::askForDate(const std::string &txt) {
  std::string dateStr = askForString(txt);
  try {
    return (dateStr == "0") ? NULL : new Date(dateStr);
  }
  catch (...) {
    std::cout << "Date is invalid" << std::endl;
  }
  return askForDate(txt);
}

Account::AccountType ListAccounts::askForType(const std::string &txt) {
  try {
    std::string typestr = askForString(txt);
    if (typestr.length() != 1)
      throw -1;
    Account::AccountType type = static_cast<Account::AccountType>(typestr[0]);
    if (type == Account::CHILD) {
      std::cout << "You are too old for this account type" << std::endl;
      return askForType(txt);
    }
    if (type != Account::NONE && type != Account::NORMAL && type != Account::OLD)
      throw -1;
    return type;
  }
  catch (...) {
    std::cout << "Type is invalid" << std::endl;
  }
  return askForType(txt);
}

Id *ListAccounts::askForId(const std::string &txt) {
  std::string idstr = askForString(txt);
  if (idstr == "0")
    return NULL;
  Id *id = new Id(idstr);
  if (getById(id) == NULL) {
    std::cout << "This account doesn't exists, try again" << std::endl;
    return askForId(txt);
  }
  if (getById(id)->getType() != Account::CHILD) {
    std::cout << "This account belong to a child, try again" << std::endl;
    return askForId(txt);
  }
  return id;
}

const std::string ListAccounts::askForString(const std::string &txt) {
  std::cout << "Enter your " << txt << " (0 to quit): ";
  std::string in;
  std::getline(std::cin, in);
  if (in.length() == 0) {
    std::cout << txt << " cannot be empty, try again" << std::endl;
    return askForString(txt);
  }
  return in;
}

User *ListAccounts::askForUser() {
  std::string fname = askForString(_listElemTypes[USER_FIRSTNAME]);
  if (fname == "0")
    return NULL;
  std::string lname = askForString(_listElemTypes[USER_LASTNAME]);
  if (lname == "0")
    return NULL;
  Date *date = askForDate(_listElemTypes[USER_BIRTHDATE]);
  if (date == NULL)
    return NULL;
  return new User(fname, lname, date);
}

void ListAccounts::addAnAccount() {
  User *newUser = askForUser();
  if (newUser == NULL)
    return;
  if ((2015 - newUser->getBirthdate()->getYear()) <= 10) {
    Id *id = askForId(_listElemTypes[ACCOUNT_TUTOR_ID]);
    if (id == NULL)
      return;
    _listAccounts.push_back(_accountFactory.createAccount(Account::CHILD, newUser, NULL, 0, getById(id)));
  }
  else {
    Account::AccountType type = askForType(_listElemTypes[ACCOUNT_TYPE]);
    if (type == Account::NONE)
      return;
    _listAccounts.push_back(_accountFactory.createAccount(type, newUser, NULL, 0));
  }
}

void ListAccounts::save() {
  std::ofstream file(_filename, std::ios::trunc);
  if (file) {
    for (Account *a : _listAccounts) {
      file << a->getId()->getId()                           << ','
           << static_cast<char>(a->getType())               << ','
           << a->getUser()->getLastName()                   << ','
           << a->getUser()->getFirstName()                  << ','
           << a->getUser()->getBirthdate()->getDateString() << ','
           << (a->getTutor() ? a->getTutor()->getId()->getId() : "") << ','
           << std::fixed << std::setprecision(2) << a->getBalance();
      for (Transaction *t : a->getTransactions()) {
        file << ',' << t->getDate()->getDateString()
             << ',' << t->getAmount();
      }
      file << std::endl;
    }
  }
}
void ListAccounts::setElemTypes() {
  _listElemTypes[USER_FIRSTNAME]   = "firstname";
  _listElemTypes[USER_LASTNAME]    = "lastname";
  _listElemTypes[USER_BIRTHDATE]   = "birthdate (YYYY-MM-DD)";
  _listElemTypes[ACCOUNT_TYPE]     = "account's type (Regular (R) or Ancient (A))";
  _listElemTypes[ACCOUNT_TUTOR_ID] = "tutor's id";
}

void  ListAccounts::load() {
  std::ifstream file(_filename);
  if (file) {
    while (file) {
      std::string line;
      if (getline(file, line))
        createFromALineCSV(line);
    }
    for (auto unlinked : _listAccountsUnlinked) {
      getById(unlinked.first)->setTutor(getById(unlinked.second));
    }
  }
  else {
    std::cerr << "Error : Cannot load file : " << _filename << std::endl;
  }
}

void  ListAccounts::createFromALineCSV(const std::string &line) {
  std::stringstream          lineStream(line);
  std::vector<std::string>  _listElems(TRANSACTIONS);

  for (int i = 0; lineStream && i < TRANSACTIONS; i++) {
    std::getline(lineStream, _listElems[i], ',');
  }
  Account *newAccount = _accountFactory.createAccount(
    static_cast<Account::AccountType>(_listElems[ACCOUNT_TYPE][0]),
    new User(_listElems[USER_FIRSTNAME], _listElems[USER_LASTNAME], new Date(_listElems[USER_BIRTHDATE])),
    new Id(_listElems[ACCOUNT_ID]),
    std::stod(_listElems[BALANCE]),
    NULL
  );
  if (_listElems[ACCOUNT_TUTOR_ID].length())
    _listAccountsUnlinked[new Id(_listElems[ACCOUNT_ID])] = new Id(_listElems[ACCOUNT_TUTOR_ID]);
  std::string transactionAmount;
  std::string transactionDate;
  while (lineStream) {
    std::getline(lineStream, transactionDate, ',');
    std::getline(lineStream, transactionAmount, ',');
    if (lineStream) {
      newAccount->addTransaction(std::stod(transactionAmount), new Date(transactionDate));
    }
  }
  _listAccounts.push_back(newAccount);
}

void ListAccounts::menu() {
  _menuListAccounts->show();
}
