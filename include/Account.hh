#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <list>

#include "User.hh"
#include "Id.hh"
#include "Transaction.hh"
#include "IdGenerator.hh"

class Account {
public:
  enum AccountType       { NORMAL = 'R', CHILD = 'E', OLD = 'A' };
  enum TransactionStatus { SUCCESS, INSUF_BALANCE, DAY_LIMIT, MONTH_LIMIT, UNAUTHORIZED };
protected:
  User                    *_user;
  Id                      *_id;
  Id                      *_tutor;
  double                   _balance;
  Account::AccountType     _type;
  std::list<Transaction *> _listTransactions;

  double getTotalWithdrawThisDay(Date *date);
  double getTotalWithdrawThisMonth(Date *date);
public:
  Account(User *user, Id *id, double balance, Id *tutor);
  const Id                       *getId()           const;
  const User                     *getUser()         const;
  const Id                       *getTutor()        const;
  const std::list<Transaction *> &getTransactions() const;
  double                          getBalance()      const;
  AccountType                     getType()         const;

  virtual TransactionStatus withdraw(const double amount, Date *date);
  virtual TransactionStatus deposit(const double amount, Date *date);
  virtual void addTransaction(const double amount, Date *date);
  virtual ~Account();
};


#endif // ACCOUNT_HH
