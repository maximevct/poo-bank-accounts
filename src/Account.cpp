#include "Account.hh"

Account::Account(User *user, Id *id, double balance, Id *tutor) {
  _user              = user;
  _balance           = balance;
  IdGenerator *idGen = IdGenerator::getInstance();
  _tutor             = tutor;
  _id                = (id == NULL) ? idGen->generateId(user) : idGen->useId(id);
  _menuAccount = new Menu<void, Account>(this, "Account ["+ _id->getId() +"] - Menu ");
  _menuAccount->push_back("Display balance", &Account::showBalance);
  _menuAccount->push_back("Make a withdraw", &Account::showWithdraw);
  _menuAccount->push_back("Make a deposit", &Account::showDeposit);
  _menuAccount->push_back("Display account information", &Account::showAccount);
  _menuAccount->push_back("List all transactions", &Account::showListTransactions);
  _transactionsStatuses.push_back("Operation completed succesfully");
  _transactionsStatuses.push_back("Your balance is insufficient");
  _transactionsStatuses.push_back("You have reached the daily withddrawal limit");
  _transactionsStatuses.push_back("You have reached the monthly withddrawal limit");
  _transactionsStatuses.push_back("Unfortunately God could not respond favorably to your request");
}

const Id                       *Account::getId()           const { return _id; }
const User                     *Account::getUser()         const { return _user; }
const Id                       *Account::getTutor()        const { return _tutor; }
const std::list<Transaction *> &Account::getTransactions() const { return _listTransactions; }
double                          Account::getBalance()      const { return _balance; }
Account::AccountType            Account::getType()         const { return _type; }

double Account::getTotalWithdrawThisDay(Date *date) {
  double sum = 0;
  for (Transaction *t : _listTransactions) {
    if (t->getDate()->compareDay(date))
      sum += t->getAmount();
  }
  return sum;
}

double Account::getTotalWithdrawThisMonth(Date *date) {
  double sum = 0;
  for (Transaction *t : _listTransactions) {
    if (t->getDate()->compareMonth(date))
      sum += t->getAmount();
  }
  return sum;
}

Account::TransactionStatus Account::withdraw(const double amount, Date *date) {
  if (_balance > amount) {
    _listTransactions.push_back(new Transaction(-amount, date));
    _balance -= amount;
    return Account::SUCCESS;
  }
  return Account::INSUF_BALANCE;
}

Account::TransactionStatus Account::deposit(const double amount, Date *date) {
  _listTransactions.push_back(new Transaction(amount, date));
  _balance += amount;
  return Account::SUCCESS;
}

void Account::addTransaction(const double amount, Date *date) {
  _listTransactions.push_back(new Transaction(amount, date));
}

Account::~Account() {}

void Account::menu() {
  _menuAccount->show();
}

void Account::showBalance() {
  std::cout << "Your balance is : " << _balance << std::endl;
}

double Account::askAmount() {
  std::cout << "Enter an amount (0 to quit): ";
  std::string amountStr;
  std::getline(std::cin, amountStr);
  try {
    double amountDbl = std::stod(amountStr);
    if (amountDbl < 0) {
      std::cout << "Amount must be positive" << std::endl;
    }
    else
      return amountDbl;
  }
  catch (...) {
    std::cout << "Amount is invalid" << std::endl;
  }
  return askAmount();
}

Date *Account::askDate() {
  std::cout << "Enter the date (YYYY-MM-DD): ";
  std::string dateStr;
  std::getline(std::cin, dateStr);
  try {
    return new Date(dateStr);
  }
  catch (...) {
    std::cout << "Date is invalid" << std::endl;
  }
  return askDate();
}

void Account::showWithdraw() {
  double amount = 0;
  Date *date = NULL;
  while (!date) {
    amount = askAmount();
    if (!amount)
      return;
    date = askDate();
  }
  std::cout << _transactionsStatuses[withdraw(amount, date)] << std::endl;
}

void Account::showDeposit() {
  double amount = 0;
  Date *date = NULL;
  while (!date) {
    amount = askAmount();
    if (!amount)
      return;
    date = askDate();
  }
  std::cout << _transactionsStatuses[deposit(amount, date)] << std::endl;
}

void Account::showAccount() {
  std::cout << std::setw(20) << "Id : " << _id << "\n"
            << std::setw(20) << "User : " << _user << "\n"
            << std::setw(20) << "Balance : " << _balance << "\n"
            << std::setw(20) << "Account type : " << static_cast<char>(_type) << std::endl;
}

void Account::showListTransactions() {
  std::cout << "Transaction list : " << std::endl;
  for (auto t : _listTransactions) {
    std::cout << "\t" << t << std::endl;
  }
}

bool operator==(Account *account, const std::string &id) {
  return account->getId() == id;
}

std::ostream &operator<<(std::ostream &os, const Account *account) {
  os << std::setw(15)
     << "[" + account->getId()->getId() + "] : "
     << account->getUser() << "\n"
     << std::setw(16)
     << "(" << static_cast<char>(account->getType()) << ") | "
     << std::fixed << std::setprecision(2) << account->getBalance();
  return os;
}
