#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "affichage.h"
#include "decoupe.h"
#include "position.h"
#include "gameplay.h"
#include "lobby.h"
#include "variables.h"


int main(void) {
  int triche=0, l, h, rec_x, rec_y, i, placement_x=900, placement_y=350, id_image, ecran_x=1600, ecran_y=1000;
  char* path_image;
  int* ordre;
  int** decoupe;
  int** position;
  couleur couleur_fond, couleur_encadre, couleur_pre_select, color_black;

  couleur_fond = CouleurParComposante(255,255,255);
  couleur_encadre = CouleurParComposante(40,40,255);
  couleur_pre_select = CouleurParComposante(255,255,0);
  color_black=CouleurParComposante(0,0,0);

  InitialiserGraphique();
  CreerFenetre(0,0,ecran_x,ecran_y);
  EffacerEcran(couleur_fond);

  while (1) {
    /* Menu d'avant-Partie */
      lobby (&rec_x,&rec_y,&id_image,&triche,couleur_fond);

      /*On alloue dynamiquement et mettons des valeurs dans des variable en fonction des choix du joueur*/
      ordre=(int*) malloc(rec_x*rec_y*sizeof(int));
      decoupe=(int**) malloc(rec_x*rec_y*sizeof(int)*INFO_DECOUPE);
      for (i=0;i<rec_x*rec_y;i++){
        decoupe[i]=(int*) malloc(INFO_DECOUPE*sizeof(int));
      }
      position=(int**) malloc(rec_x*rec_y*sizeof(int)*INFO_POSITION);
      for (i=0;i<rec_x*rec_y;i++){
        position[i]=(int*) malloc(INFO_POSITION*sizeof(int));
      }
      switch (id_image) {
        case 1:
        path_image=PATH_IMAGE1;
        l=L_IMAGE1, h=H_IMAGE1;
        break;
        case 2:
        path_image=PATH_IMAGE2;
        l=L_IMAGE2, h=H_IMAGE2;
        break;
        case 3:
        path_image=PATH_IMAGE3;
        l=L_IMAGE3, h=H_IMAGE3;
        break;
      }

      /*Découpage de l'image en tuile, on envoie entre autres le tableau decoupe qui est vide pour y mettre le découpage et les infos de chaque tuile, on envoie également le tableau
      position, qui est vide pour y mettre les emplacements possibles pour les tuiles*/
      decoupage(l,h,rec_x,rec_y,decoupe,position,placement_x,placement_y);
      /*Détermination de l'ordre dans lequel afficher les tuiles, on lui envoie entre autre le tableau ordre qui est vide, pour y mettre l'ordre de disposition des tuiles*/
      repartition(ordre,rec_x,rec_y,triche);

      /*Affichage du corps de la partie*/
      EffacerEcran(couleur_fond);
      ChargerImage(path_image,100,placement_y+(rec_y*MARGE)/2,0,0,l,h);
      ChoisirCouleurDessin(color_black);
      EcrireTexte(50,50,"Votre but est de deplacer les tuiles qui sont a droite, pour reproduire l'image de gauche.",1);
      EcrireTexte(50,90,"Voici quelques informations sur comment jouer :",1);
      ChoisirCouleurDessin(couleur_encadre);
      EcrireTexte(50,120,"Clique gauche",1);
      EcrireTexte(50,140,"Fleches directionnelles",1);
      EcrireTexte(50,160,"Barre d'espace",1);
      ChoisirCouleurDessin(color_black);
      EcrireTexte(300,120,": vous permet de selectionner une tuile a deplacer (re-cliquer sur l'enplacement vide pour l'y deplacer)",1);
      EcrireTexte(300,140,": vous permet de vous deplacer sur les tuiles",1);
      EcrireTexte(300,160,": vous permet de selectionner la tuile sur laquelle vous vous etes deplace",1);
      /*On affiche les tuiles en se servant de decoupe, pour les dimensions des tuiles, position, pour pouvoire placer les tuiles dans la fenêtre et ordre, pour savoir dans quel
      ordre les placer*/
      affichage(decoupe,position,ordre,l,h,rec_x,rec_y,path_image);

      /*Exécution de la partie*/
      if(gameplay(decoupe,position,ordre,l,h,rec_x,rec_y,placement_x,placement_y,couleur_fond, couleur_encadre, couleur_pre_select,path_image)==0){
        /* L'utilisateur veut quitter le jeu */
        break;
      }
      /* Reset du fond et de la variable "triche" car l'utilisateur a demandé a rejouer */
      triche=0;
      EffacerEcran(couleur_fond);
  }
  /*On ferme la fenêtre et libère l'espace occupé par les variables dont la mémoire à été allouée dynamiquement*/
  FermerGraphique();
  free(decoupe);
  free(position);
  free(ordre);
  return EXIT_SUCCESS;
}
