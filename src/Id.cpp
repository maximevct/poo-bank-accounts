#include "Id.hh"

Id::Id(const std::string &id) : _id(id) {}
Id::~Id() {}

const std::string &Id::getId() const { return _id; }

bool operator==(Id* idObj, const std::string &idStr) {
  return idObj->getId() == idStr;
}

std::ostream &operator<<(std::ostream &os, const Id *id) {
  os << id->getId();
  return os;
}
