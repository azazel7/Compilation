Compiler
========

Pour compiler l'application, il faut exécuter la commande « make » ou « make -j ».

Usage
=====

Pour compiler le fichier « poisson.c », exécutez la commande « gazl poisson.c », ce qui aura pour effet de générer le fichier « poisson.s ».
Ensuite, il ne reste plus qu'à faire « gcc poisson.s -o poisson ».
Si vous utilisez des fonctions intégrées comme « malloc_int » ou « print_int », la commande devient « gcc poisson.s buildin.c -o poisson ».
Si vous utilisez la boucle parralléle, la commande devient « gcc poisson.s pfor.c -o poisson -lpthread ».

64 bit -> buildin et pfor ne parche pas.
64 bit -> pensez à utiliser -m32
Ne pas empiler les boucle para
Pas de déclaration externe
Malloc est buggué


