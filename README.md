Compiler
========

Pour compiler l'application, il faut exécuter la commande « make » ou « make -j ».
L'exécutable « gazl » doit être apparu.

Usage
=====

Pour compiler le fichier « poisson.c », exécutez la commande « gazl poisson.c », ce qui aura pour effet de générer le fichier « poisson.s ».
Ensuite, il ne reste plus qu'à faire « gcc poisson.s -o poisson » pour obtenir un exécutable. Notez au passage qu'il faudra sans doute ajouter l'option « -m32 » pour compiler sur une machine 64 bits.
Si vous utilisez des fonctions intégrées comme « printint » ou « printfloat », la commande devient « gcc poisson.s buildin.c -o poisson ». Pour une machine 64 bits, il est possible que des erreurs surviennent au moment du *link* car vous ne disposez pas des librairies 32 bits.
Si vous utilisez la boucle parallèle, la commande devient « gcc poisson.s pfor.c -o poisson -lpthread ». Même remarque que précédement pour les machines 64 bits.
Pour lancer la compilation sur tous les fichiers de test du dossier « tests », lancez le script « ./test.sh ».
Attention, les tests ne générent que des fichiers assembleur qu'il faudra ensuite assembler et *linker* au besoin avec les commandes gcc fournises plus haut.

Le compilateur
==============

Le compilateur génère du code 32 bits.
Il a été écrit en C++ essentiellement pour profiter des structures proposées par la STL comme les *map* ou les *list*. Par ailleurs nous faisons un usage intensif de l'héritage et des exceptions.
Il a été fait comme choix de construire complétement l'arbre syntaxique correspondant au code source durant l'exécution des différentes règles de la grammaire puis de travailler dessus. 
Ce qui explique notamment que l'on peut appeler des fonctions qui seront déclarées plus bas dans le code source.
La transmission des valeurs et des résultats se fait sur la pile à l'exception des fonctions qui renvoient leur résultat dans le registre aex par soucis de standard et de technique. (L'instruction ret effectuant un pop de l'adresse de retour).
Par ailleurs, le compilateur remplit les critères suivant :
* Les types de base sont *void*, *int* et *float*
* Les types construits sont les tableaux et les fonctions.
* Les tableaux ne peuvent avoir qu'une seule dimension
* Les tableaux peuvent être alloués dynamiquement ou statiquement
* Les tableaux peuvent être déclarés comme des pointeurs ou des tableaux.
* Les fonctions sont globales.
* Les paramètres d'une fonction peuvent être des tableaux, des entiers, des flottants ou des pointeurs.
* Les fonctions « printint(int) » et « printfloat(float) » seront connues par l'utilisateur et pourront être utilisées sans déclaration.
* Les règles de typage sont celles du C.
* L'affectation fonctionne comme en C
* Un tableau statique ne peut pas être à gauche d'une affectation.
* Les boucles *for* et *while* se comportent comme en C.
* Le *if* peut avoir une partie *else*.
* Les blocs d'instructions fonctionnent comme en C.

Les tests
=========

Le test t6.c ne passe pas, car il n'est pas possible de déclarer une fonction par son seul prototype.
Les tests tp2.c, tp3.c, tp7.c, tp8.c, tp9.c et tp10.c sont des tests sensés générer des erreurs sémantiques ou syntaxiques.
Les test tc4.c, tc5.c, tc6.c et tc7.c doivent aussi générer des erreurs.
* tc4.c = Affectation d'un entier à un tableau statique.
* tc5.c = Affectation d'un entier à un pointeur.
* tc6.c = Erreur dans les types des arguments
* tc7.c = Erreur dans le nombre d'arguments.

Problèmes
=========

Il n'est possible de compiler qu'un unique fichier à la fois.
Le compilateur implémente l'extension de la boucle parallèle, mais les boucles parallèles ne doivent pas être emboitées d'une quelconque manière. Soit dans le corp de la boucle, soit dans l'empilement des fonctions.
Il est impossible de déclarer des fonctions externes par leur seul prototype comme en C.
Il existe deux fonctions malloc_int et malloc_float qui sont sensées allouer dynamiquement des tableaux. Bien qu'elles puissent être appelées, leur fonctionnement n'est pas une science exacte.
De plus, les opérations sur les pointeurs sont autorisées.
Les variables de type void sont autorisées bien que presque inutilisables car aucun *cast* automatique n'est effectué.
Il est possible de déclarer dans une fonction un prototype de la forme « int i(int a); ». Étant donné que nous ne prenons pas en compte les prototypes, cette déclaration est équivalente à « int i; ». Donc bien que cela soit possible, aucune fonction n'est crée à l'intérieur de la fonction.
