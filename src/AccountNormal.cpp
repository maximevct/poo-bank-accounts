#include "AccountNormal.hh"

AccountNormal::AccountNormal(User *user, Id *id, double balance, Id *tutor) : Account(user, id, balance, tutor) {
  _type = NORMAL;
}

AccountNormal::~AccountNormal() {}
