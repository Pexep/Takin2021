#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "decoupe.h"
#include "variables.h"

int decoupage(int l_image, int h_image, int rec_x, int rec_y, int** decoupe, int** position,int placement_x,int placement_y){
    int l, h, x=0, y=0, i=0; /* Valeurs de base */

    l = l_image/rec_x, h=h_image/rec_y; /* Calcul des valeurs étalons pour la taile des tuiles */

    /*On rempli les tableau decoupe (informations sur la position des tuiles dans l'image originale) et le tableau position (informations sur les emplacements auxquels mettre des tuiles)*/
    while (x<rec_x) {
        if(y<rec_y && y>=0){

          decoupe[i][0]=i;
          decoupe[i][1]=x*l;
          decoupe[i][2]=y*h;

          position[i][0]=i;
          position[i][1]=(x*MARGE)+(x*l)+placement_x;
          position[i][2]=(y*MARGE)+(y*h)+placement_y;

          y++;
        }
        else{
          y=0;
          x++;
          i=i-1;
        }
        i++;
    }
    return EXIT_SUCCESS;
}
