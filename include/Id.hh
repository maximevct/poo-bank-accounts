#ifndef ID_HH
#define ID_HH

#include <string>

class Id {
private:
  const std::string _id;
public:
  Id(const std::string &id);
  ~Id();

  const std::string &getId() const;
};

bool operator==(Id* idObj, const std::string &idStr);
std::ostream &operator<<(std::ostream &os, const Id *id);

#endif // ID_HH
