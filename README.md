Compiler
========

Pour compiler l'application, il faut exécuter la commande « make » ou « make -j ».

Usage
=====

Pour compiler le fichier « poisson.c », exécutez la commande « gazl poisson.c », ce qui aura pour effet de générer le fichier « poisson.s ».
Ensuite, il ne reste plus qu'à faire « gcc poisson.s -o poisson » pour obtenir un exécutable. Notez au passage qu'il faudra sans doute ajouter l'option -m32 pour compiler sur une machine 64 bits.
Si vous utilisez des fonctions intégrées comme « malloc_int » ou « print_int », la commande devient « gcc poisson.s buildin.c -o poisson ». Pour une machine 64 bits, il est possible que des erreurs surviennent au moment du link car vous ne disposez pas des librairie 32 bits.
Si vous utilisez la boucle parralléle, la commande devient « gcc poisson.s pfor.c -o poisson -lpthread ». Même remarque que précédement pour les machines 64 bits.
Pour lancer la compilation sur tous les fichiers de test du dossier « tests », lancez le script « ./test.sh ».

Le compilateur
==============

Le compilateur générere du code 32 bits.
Il a été écrit en C++ essentiellement pour profiter des structures proposées par la STL comme les map ou les list. Par ailleurs nous faisons un usage intensif de l'héritage et des exceptions.
Il a été fait comme choix de construire complétement l'arbre syntaxique correspondant au code source durant l'exécution des différentes régles de la grammaire puis de travailler dessus. 
Ce qui explique nottement que l'on peut appeler des fonctions qui seront déclarées plus bas dans le code source.

Problémes
=========

Il n'est possible de compiler qu'un unique fichier à la fois.
Le compilateur implémente l'extension de la boucle parralélle, mais les boucles parralléles ne doivent pas être emboitées d'une quelconque manière. Soit dans le corp de la boucle, soit dans l'empilement des fonctions.
Il est impossible de déclarer des fonctions externes par leur seule prototype comme en C.
Il existe deux fonctions malloc_int et malloc_float qui sont sensées allouer dynamiquement des tableaux. Bien qu'elles puissent être appelées, leur fonctionnement n'est pas une science exacte.
De plus, les opérations sur les pointeurs sont autorisées.

