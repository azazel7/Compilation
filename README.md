Compiler
========

Pour compiler l'application, il faut exécuter la commande « make » ou « make -j ».

Usage
=====

Pour compiler le fichier « poisson.c », exécutez la commande « gazl poisson.c », ce qui aura pour effet de générer le fichier « poisson.s ».
Ensuite, il ne reste plus qu'à faire « gcc poisson.s -o poisson » pour obtenir un exécutable. Notez au passage qu'il faudra sans doute ajouter l'option -m32 pour compiler sur une machine 64 bits.
Si vous utilisez des fonctions intégrées comme « malloc_int » ou « print_int », la commande devient « gcc poisson.s buildin.c -o poisson ». Pour une machine 64 bits, il est possible que des erreurs surviennent au moment du link car vous ne disposez pas des librairie 32 bits.
Si vous utilisez la boucle parralléle, la commande devient « gcc poisson.s pfor.c -o poisson -lpthread ». Même remarque que précédement pour les machines 64 bits.


Le compilateur
==============

Ne pas empiler les boucle para
Pas de déclaration externe
Malloc est buggué


