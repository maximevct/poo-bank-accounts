#ifndef ID_GENERATOR_HH
#define ID_GENERATOR_HH

#include "Id.hh"
#include "User.hh"

#include <list>
#include <algorithm>

class IdGenerator {
private:
  static IdGenerator *_instance;
  std::list<Id *>     _listIds;

  IdGenerator();
  bool  issetId(const std::string &);
  Id *createNewId(const std::string &);

public:
  static IdGenerator *getInstance();
  ~IdGenerator();
  Id *useId(Id *);
  Id *generateId(User *, const int = 1);
};


#endif // ID_GENERATOR_HH
