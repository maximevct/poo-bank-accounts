#ifndef ID_HH
#define ID_HH

#include <string>

class Id {
private:
  const std::string _id;
public:
  Id(const std::string &);
  ~Id();

  const std::string &getId() const;
};

bool operator==(Id *, const std::string &);
std::ostream &operator<<(std::ostream &, const Id *);

#endif // ID_HH
