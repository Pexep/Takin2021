
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "affichage.h"
#include "variables.h"

void affichage(int** decoupe, int** position, int ordre[], int l_image, int h_image, int rec_x, int rec_y, char* path_image){
  int i, l, h, nb_tuile=rec_x*rec_y;

  l = l_image/rec_x, h=h_image/rec_y; /* Calcul des valeurs étalons pour la taile des tuiles */

  /*On affiche les tuiles (dont la place dans l'image est définie dans le tableau decoupe), dans des cases (dont l'emplacement est défini dans le tableau position) et dans un certain ordre (précisé dans le tableau ordre)*/
  for (i=0;i<nb_tuile;i++){
    if (ordre[i]!=0){
      ChargerImage(path_image,position [i][1],position [i][2],decoupe [ordre[i]][1],decoupe [ordre[i]][2],l,h);
    }
  }
}
