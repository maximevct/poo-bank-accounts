#ifndef MENU_HH
#define MENU_HH

#include <vector>
#include <string>
#include <iostream>

#include <typeinfo>

template<typename T, typename U>
class Menu {
  std::vector<std::string>  _listChoices;
  std::vector<T (U::*)()>            _listFunctions;
  U *_context;
public:
  Menu(U *context) {
    _context = context;
  }
  ~Menu() {}

  void push_back(const std::string &choice, T (U::*func)()) {
    _listChoices.push_back(choice);
    _listFunctions.push_back(func);
  }

  void show() {
    int i = 0;
    for (auto choice : _listChoices) {
      std::cout << i++ << "] " << choice << std::endl;
    }
    std::cout << "Enter your choice : ";
    int entry = 0;
    std::cin >> entry;
    if (entry > _listChoices.size()) {
      std::cout << "Invalid Choice" << std::endl;
      show();
    }
    std::cout << entry << std::endl;
    (_context->*_listFunctions[entry])();
  }
};

#endif // MENU_HH
