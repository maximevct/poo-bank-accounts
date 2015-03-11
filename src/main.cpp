#include "main.hh"

int     main(int ac, char *av[]) {
  ListAccounts *listAccounts;
  if (ac == 2) {
    listAccounts = new ListAccounts(av[1]);
    listAccounts->load();
  }
  else {
    listAccounts = new ListAccounts();
  }
  listAccounts->menu();
  if (ac == 2)
    listAccounts->save();
  delete listAccounts;
  return 0;
}
