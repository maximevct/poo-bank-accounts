Programmation orientée objet
============================

## TP 2

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

### Auteur
Maxime VINCENT
