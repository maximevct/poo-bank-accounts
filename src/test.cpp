#include <cstdlib>
#include <iostream>

static int _nbrDecision = 0;

int myRand() {
  int value1 = rand() % 2;
  int value2 = rand() % 10;
  int value3 = rand() % 42 + 12;
  int nbrTry = 0;
  while (value2 != 7) {
    nbrTry++;
    value2 = rand() % 10;
  }
  value3 /= nbrTry + 1;
  return value1 == (value3 > value2);
}

int main() {
  for (int i = 0; i < 50; i++) {
    std::cout << myRand() << std::endl;
  }
}
