#include "main.hh"

int     main(int ac, char *av[]) {
  if (ac == 2) {
    ListAccounts    listAccounts(av[1]);
    listAccounts.load();
    listAccounts.menu();
    listAccounts.save();
  }
  return 0;
}
