#include "Transaction.hh"

Transaction::Transaction(double amount, Date *date, Status status)
  : _amount(amount) {
    _date = date;
    _status = status;
  }

double              Transaction::getAmount() const { return _amount; }
Date               *Transaction::getDate()   const { return _date;   }
Transaction::Status Transaction::getStatus() const { return _status; }

std::ostream &operator<<(std::ostream & os, Transaction *t) {
  os << t->getDate() << " -> " << t->getAmount() << " [" << ((t->getStatus() == Transaction::SUCCESS) ? "OK" : "KO") << "]";
  return os;
}
