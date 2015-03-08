#include "Id.hh"

Id::Id(const std::string &id) : _id(id) {}
Id::~Id() {}

const std::string &Id::getId() const { return _id; }

bool Id::operator==(Id *id) {
  return getId() == id->getId();
}

bool Id::operator==(const std::string &id) {
  return getId() == id;
}

bool operator==(const Id* idObj, const std::string &idStr) {
  return idObj->getId() == idStr;
}

std::ostream &operator<<(std::ostream &os, const Id *id) {
  os << id->getId();
  return os;
}
