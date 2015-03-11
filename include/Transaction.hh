#ifndef TRANSACTION_HH
#define TRANSACTION_HH

#include "Date.hh"

class Transaction {
public:
  enum Status { SUCCESS, INSUF_BALANCE, DAY_LIMIT, MONTH_LIMIT, UNAUTHORIZED };

private:
  double _amount;
  Date   *_date;
  Status _status;

public:
  Transaction(double, Date *, Status = SUCCESS);
  double getAmount() const;
  Date  *getDate()   const;
  Status getStatus() const;
};

std::ostream &operator<<(std::ostream &, Transaction *);

#endif // TRANSACTION_HH
