#include <list>
#include <string>
#include <iostream>

class Account {
public:
  std::string _f, _l;
  Account(const std::string &f, const std::string &l) :_f(f), _l(l) {}

  virtual void print() { std::cout << "Hello from Account " << std::endl;}
};

class AccountChild : public Account {
public:
  AccountChild(const std::string &f, const std::string &l) : Account(f, l) {}

  void print() { std::cout << "Hello from Account Child" << std::endl;}
};

class AccountOld : public Account {
public:
  AccountOld(const std::string &f, const std::string &l) : Account(f, l) {}

  void print() { std::cout << "Hello from Account Old" << std::endl;}
};

class ListAccounts {
private:
  std::list<Account *> _listAccount;

public:
  ListAccounts() {}
  ~ListAccounts() {}

  template<typename T>
  void createAccount(const std::string &firstName, const std::string &lastName) {
    _listAccount.push_back(new T(firstName, lastName));
  }

  void disp() {
    for (Account *a : _listAccount) {
      std::cout << a->_f  << " " << a->_l << " - ";
      a->print();
    }
  }
};

int main() {
  ListAccounts lAccount;

  lAccount.createAccount<AccountChild>("Ella", "Nut");
  lAccount.createAccount<AccountOld>("Andin", "Norm");
  lAccount.disp();
}
