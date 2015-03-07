#include "Transaction.hh"

Transaction::Transaction(double amount, Date *date)
  : _amount(amount) {
    _date = date;
  }

double Transaction::getAmount() const { return _amount; }
Date  *Transaction::getDate()   const { return _date;   }
