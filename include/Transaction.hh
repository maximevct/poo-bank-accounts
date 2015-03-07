#ifndef TRANSACTION_HH
#define TRANSACTION_HH

#include "Date.hh"

class Transaction {
private:
  double _amount;
  Date  *_date;
public:
  Transaction(double amount, Date *date);
  double getAmount() const;
  Date  *getDate()   const;
};

#endif // TRANSACTION_HH
