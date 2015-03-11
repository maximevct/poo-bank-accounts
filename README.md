Programmation orientée objet
============================

## TP 2 - Partie 1

### Environnement de développement
  - Système : Ubuntu 14.04 LTS (64 bits)
  - Editeur : Sublime Text 2
  - Compilateur : g++

### Fichiers
  - **src**
    - AccountChild.cpp
    - Account.cpp
    - AccountFactory.cpp
    - AccountNormal.cpp
    - AccountOld.cpp
    - Date.cpp
    - God.cpp
    - Id.cpp
    - IdGenerator.cpp
    - ListAccounts.cpp
    - main.cpp
    - test.cpp
    - Transaction.cpp
    - User.cpp
  - **include**
    - AccountChild.hh
    - AccountFactory.hh
    - Account.hh
    - AccountNormal.hh
    - AccountOld.hh
    - Date.hh
    - God.hh
    - IdGenerator.hh
    - Id.hh
    - ListAccounts.hh
    - main.hh
    - Menu.hh
    - Transaction.hh
    - User.hh
  - Makefile
  - answer2.cpp
  - README.md
  - **dataset**
    - banque.csv

### Comment l'utiliser :
```bash
  $ make
  $ ./tp2 [filename.csv]
```

### Fonctionalités :
  - Affichage de la liste des utilisateurs
  - Séléction d'un utilisateur
  - Ajout d'un utilisateur
  - Suppression d'un utilisateur
  - **Compte**
    - Affichage du solde du compte
    - Retrait (Compte enfant (E) limité à 10/jour et 50/mois, Compte ancien (A) requiert autorisation de Dieu)
    - Dépôt
    - Afficher les informations du compte
    - Afficher toutes les transactions
    - Afficher uniquement les transactions valides
    - Afficher le tuteur (Compte enfant uniquement)

### CSV Format :
```csv
ID_ACCOUNT,ACCOUNT_TYPE,LASTNAME,FIRSTNAME,BIRTHDATE,[TUTOR_ID_ACCOUNT],BALANCE,[AMOUNT_TRANSACTION,DATE_TRANSACTION]
```

## TP 2 - Partie 2

Le projet aurait pu être codé en utilisant une classe paramétrée qui aurait pris la forme suivante :
```C++
class ListAccounts {
private:
  std::list<Account *> _listAccount;

public:
  ListAccounts() {}
  ~ListAccounts() {}

  template<typename T>
  void createAccount(const std::string &firstName, const std::string &lastName) {
    _listAccount.push_back(new T(firstName, lastName));
  }
};

int main() {
  ListAccounts lAccount;

  lAccount.createAccount<AccountChild>("Ella", "Nut");
}
```

Vous pouvez trouver un exemple fonctionnel dans le fichier `answer2.cpp` à compiler avec : `g++ answer2.cpp -std=c++11`

Cette solution peut paraitre plus simple à coder et à utiliser mais il nous oblige a connaitre le type de compte. Il faut donc écrire autant de fois d'appel à la fonction `createAccount` qu'il existe de comptes différents. La solution la plus adéquate pour ce projet est, il me semble, l'utilisation du pattern `Factory` couplé à un vector contenant des pointeurs sur les méthodes de création de chacun des types. Ainsi, la gestion des constructeurs se fait uniquement grâce à un tableau que l'on rempli ou non.

Une classe paramétrée a été utilisée dans le projet afin de créer dynamiquement les menu. Elle est écrite dans le fichier `menu.hh` et est utilisée dans les classes `ListAccounts` et `Accounts`

### Auteur
Maxime VINCENT
