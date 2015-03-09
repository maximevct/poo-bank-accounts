#ifndef MENU_HH
#define MENU_HH

#include <vector>
#include <string>
#include <iostream>

template<typename T, typename U>
class Menu {
  std::vector<std::string>  _listChoices;
  std::vector<T (U::*)()>            _listFunctions;
  U *_context;
  std::string _title;
public:
  Menu(U *context, const std::string &title) : _title(title) {
    _context = context;
    _listChoices.push_back("Quit");
    _listFunctions.push_back(NULL);
  }
  ~Menu() {}

  void push_back(const std::string &choice, T (U::*func)()) {
    _listChoices.push_back(choice);
    _listFunctions.push_back(func);
  }

  void show() {
    int entry = -1;
    while (entry != 0) {
      int i = 0;
      std::cout << "|------" << _title << std::setfill('-') << std::setw(50 - _title.length()) << "|" << std::setfill(' ') << std::endl;
      for (auto choice : _listChoices) {
        std::cout << "|" << std::setw(4) << i++ << "] " << choice << std::setw(50 - choice.length()) << "|" << std::endl;
      }
      std::cout << "|" << std::setfill('-') << std::setw(56) << "|" << std::setfill(' ') << std::endl;
      std::cout << "Enter your choice : ";
      std::string entryStr;
      std::getline(std::cin, entryStr);
      try {
        entry = std::stoi(entryStr);
        if (entry >= _listChoices.size()) {
          throw -1;
        }
        else if (entry) {
          (_context->*_listFunctions[entry])();
        }
      }
      catch (...) {
        std::cout << "Invalid Choice" << std::endl;
        entry = -1;
      }
    }
  }
};

#endif // MENU_HH
