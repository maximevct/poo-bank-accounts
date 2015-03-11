#include "IdGenerator.hh"

IdGenerator *IdGenerator::_instance = NULL;

IdGenerator::IdGenerator() {}
IdGenerator::~IdGenerator() {}

bool IdGenerator::issetId(const std::string &id) {
  std::list<Id *>::iterator it;
  it = find(_listIds.begin(), _listIds.end(), id);
  return it != _listIds.end();
}

Id *IdGenerator::createNewId(const std::string &id) {
  Id *newId = new Id(id);
  _listIds.push_back(newId);
  return newId;
}

IdGenerator *IdGenerator::getInstance() {
  if (_instance == NULL) {
    _instance = new IdGenerator();
  }
  return _instance;
}

Id *IdGenerator::useId(Id *id) {
  _listIds.push_back(id);
  return id;
}

Id *IdGenerator::generateId(User *user, const int i) {
  std::string idAsString;
  idAsString = std::to_string(i);
  return (issetId(idAsString)) ? generateId(user, i + 1) : createNewId(idAsString);
}
