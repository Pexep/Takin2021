#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>
#include "variables.h"
#include "position.h"

int repartition(int ordre [], int rec_x, int rec_y, int triche){
  int i=0,j, randomove=0, selection=0, check[4], nb_tuile=rec_x*rec_y, nb_deplacement,deplacement,case_zero;

  /*On rempli le tableau qui détermine l'ordre des tuiles pour pouvoir les mélanger*/
  for (i=0;i<nb_tuile;i++){
    ordre[i]=i;
  }

  /*Si le bouton triche n'a pas été selectionné, on mélange les tuiles. Si il a été sélectionné, on inverse seleument la première et la deuxième tuile*/
  if (triche==0){
    srand(time(NULL));
    selection=0, case_zero=0;

    /* On effectue des mouvements possibles sur les tuiles, de manière aléatoire. On effectue un nombre de mouvement égal à BRASSAGE constante globale définie dans variables.h*/
    for(i = 0; i<BRASSAGE; i++){

      /*On rentre dans un premier temps les déplacements possibles dans le tableau check*/
      check[0]=0, check[1]=0, check[2]=0, check[3]=0;
      if(case_zero<rec_y*(rec_x-1)){
        check[0]=1;
      }
      if(case_zero>=rec_y){
        check[1]=1;
      }
      if(case_zero%rec_y!=0){
        check[2]=1;
      }
      if((case_zero+1)%rec_y!=0){
        check[3]=1;
      }

      /* Sélection du mouvement à appliquer, de manière aléatoire*/
      randomove=rand()%4;
      while(check[randomove]==0){
        randomove=rand()%4;
      }
      deplacement=randomove;
      if (deplacement==0){
        selection=case_zero+rec_y;
      }
      if (deplacement==1){
        selection=case_zero-rec_y;
      }
      if (deplacement==2){
        selection=case_zero-1;
      }
      if (deplacement==3){
        selection=case_zero+1;
      }

      /* Permutation des tuiles */
      ordre[case_zero]=ordre[selection];
      ordre[selection]=0;
      case_zero=selection;
    }
  }else{
    ordre[0]=1, ordre[1]=0;
  }
  return EXIT_SUCCESS;
}
