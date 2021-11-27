#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "affichage.h"


int main(void) {

  int l=474, h=474, marge=15, rec=3;

  InitialiserGraphique();
  CreerFenetre(0,0,rec*marge+l-marge,rec*marge+h-marge);

  affichage(l, h, marge, rec);

  Touche(); /* Condition de fin d'éxecution (Si une touche est pressé) */
  FermerGraphique();

  return EXIT_SUCCESS;
}
