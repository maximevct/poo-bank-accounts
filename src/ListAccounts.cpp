#include "ListAccounts.hh"

void  ListAccounts::createFromALineCSV(const std::string &line) {
  std::stringstream          lineStream(line);
  std::vector<std::string>  _listElems(TRANSACTIONS);

  for (int i = 0; lineStream && i < TRANSACTIONS; i++) {
    std::getline(lineStream, _listElems[i], ',');
  }
  Account *newAccount = _accountFactory.createAccount(
    static_cast<Account::AccountType>(_listElems[ACCOUNT_TYPE][0]),
    new User(_listElems[USER_FIRSTNAME],
      _listElems[USER_LASTNAME],
      new Date(_listElems[USER_BIRTHDATE])),
    new Id(_listElems[USER_ID]),
    std::stod(_listElems[BALANCE]),
    (_listElems[ACCOUNT_TUTOR_ID].length() ? (new Id(_listElems[ACCOUNT_TUTOR_ID])) : NULL)
  );

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

ListAccounts::ListAccounts(const std::string &filename) : _filename(filename) {
  _menuListAccounts = new Menu<void, ListAccounts>(this, "Main Menu");
  _menuListAccounts->push_back("Display account list", &ListAccounts::displayListAccounts);
  _menuListAccounts->push_back("Select an account"   , &ListAccounts::selectAnAccount);
  _menuListAccounts->push_back("Add an account"      , &ListAccounts::addAnAccount);
}

ListAccounts::~ListAccounts() {}

void ListAccounts::displayListAccounts() {
  std::cout << "List of all accounts :" << std::endl;
  for (Account *a : _listAccounts) {
    std::cout << a << std::endl;
    std::cout << std::setfill('=') << std::setw(70) << "" << std::setfill(' ') << std::endl;
  }
}

Account *ListAccounts::getById(const std::string &id) {
  std::list<Account *>::iterator it;
  it = find(_listAccounts.begin(), _listAccounts.end(), id);
  return (it != _listAccounts.end() ? *it : NULL);
}

void ListAccounts::selectAnAccount() {
  std::string id;
  std::cout << "Enter the ID account (0 to quit): ";
  std::getline(std::cin, id);
  Account *selected = getById(id);
  if (!selected)
    return;
  if (selected) {
    std::cout << selected << std::endl;
    selected->menu();
  }
  else {
    std::cout << "Invalid Id, try again" << std::endl;
    selectAnAccount();
  }
}

void ListAccounts::addAnAccount() {

}

void  ListAccounts::load() {
  std::ifstream file(_filename);
  if (file) {
    while (file) {
      std::string line;
      if (getline(file, line))
        createFromALineCSV(line);
    }
  }
  else {
    std::cerr << "Error : Cannot load file : " << _filename << std::endl;
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
           << (a->getTutor() ? a->getTutor()->getId() : "") << ','
           << std::fixed << std::setprecision(2) << a->getBalance();
      for (Transaction *t : a->getTransactions()) {
        file << ',' << t->getDate()->getDateString()
             << ',' << t->getAmount();
      }
      file << std::endl;
    }
  }
}

void ListAccounts::menu() {
  _menuListAccounts->show();
}
