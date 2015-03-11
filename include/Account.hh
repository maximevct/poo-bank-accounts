#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <list>
#include <map>

#include "User.hh"
#include "Id.hh"
#include "Transaction.hh"
#include "IdGenerator.hh"
#include "Menu.hh"

class Account {
public:
  enum AccountType { NORMAL = 'R', CHILD = 'E', OLD = 'A', NONE = '0'};
private:
  void initMenu();
  void initTransactionStatuses();
protected:
  User                                         *_user;
  Id                                           *_id;
  Account                                      *_tutor;
  double                                        _balance;
  Account::AccountType                          _type;
  std::list<Transaction *>                      _listTransactions;
  std::map<Transaction::Status, std::string>    _transactionsStatuses;
  Menu<void, Account>                           *_menuAccount;

public:
  Account(User *, Id *, double, Account *);
  virtual ~Account();
  Id                             *getId()           const;
  User                           *getUser()         const;
  Account                        *getTutor()        const;
  const std::list<Transaction *> &getTransactions() const;
  double                         getBalance()       const;
  AccountType                    getType()          const;
  void                           setTutor(Account *);

  virtual Transaction::Status withdraw(const double, Date *, Transaction::Status = Transaction::SUCCESS);
  virtual Transaction::Status deposit(const double, Date *);
  virtual void                addTransaction(const double, Date *);

  double askAmount();
  Date   *askDate();

  virtual void menu();

  virtual void showBalance();
  virtual void showWithdraw();
  virtual void showDeposit();
  virtual void showAccount();
  virtual void showListTransactions();
  virtual void showListTutor();
  virtual void showListSuccessTransactions();
};

bool operator==(Account *, const std::string &);
std::ostream &operator<<(std::ostream &, const Account *);

#endif // ACCOUNT_HH
