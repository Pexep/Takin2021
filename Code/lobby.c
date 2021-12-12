
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <string.h>
#include "lobby.h"
#include "variables.h"

/*Fonction pour encadrer*/
void Encadre2 (int , int ,int ,int , couleur, int);

void lobby (int* rec_x,int* rec_y,int* id_image,  int* triche, couleur couleur_fond){
  int i,x,y,l=200, h=200, place_image[3],placement_x=50, placement_y=200, placement_x_moins=200,placement_x_plus=350, placement_y_recx=600,placement_y_recy=800, clique=0, id_image_selected=0,premier_image_select=1,flag=0;
  couleur color_blue=CouleurParComposante(0,0,255), color_black=CouleurParComposante(0,0,0);
  char char_rec_x[2], char_rec_y[2];

  *rec_x=3;
  *rec_y=3;
  char_rec_x[0]=(*rec_x)+'0';
  char_rec_x[1]='\0';
  char_rec_y[0]=(*rec_y)+'0';
  char_rec_y[1]='\0';
  place_image[0]=placement_x;
  place_image[1]=placement_x+l+100;
  place_image[2]=placement_x+l*2+200;
  *id_image=0;

  /*On affiche le menu d'avant partie*/
  ChoisirCouleurDessin(color_black);
  EcrireTexte(50,150,"Choisissez une image :",2);
  ChargerImage(PATH_IMAGE1_VUE,placement_x,placement_y,0,0,l,h);
  ChargerImage(PATH_IMAGE2_VUE,placement_x+l+100,placement_y,0,0,l,h);
  ChargerImage(PATH_IMAGE3_VUE,placement_x+l*2+200,placement_y,0,0,l,h);
  ChargerImage(PATH_TRICHE,1400,700,0,0,127,50);
  EcrireTexte(1350,680,"Un curieux bouton ...",1);
  ChargerImage(PATH_PLAY,700,900,0,0,200,51);
  Encadre2(700,900,200,51,color_black,3);
  ChargerImage(PATH_MOINS,placement_x_moins,placement_y_recx,0,0,50,50);
  Encadre2(placement_x_moins,placement_y_recx,50,50,color_black,3);
  ChargerImage(PATH_PLUS,placement_x_plus,placement_y_recx,0,0,50,50);
  Encadre2(placement_x_plus,placement_y_recx,50,50,color_black,3);
  ChargerImage(PATH_MOINS,placement_x_moins,placement_y_recy,0,0,50,50);
  Encadre2(placement_x_moins,placement_y_recy,50,50,color_black,3);
  ChargerImage(PATH_PLUS,placement_x_plus,placement_y_recy,0,0,50,50);
  Encadre2(placement_x_plus,placement_y_recy,50,50,color_black,3);
  EcrireTexte(50,550,"Choisissez le nombre de colonnes :",2);
  EcrireTexte(placement_x_moins+80,placement_y_recx+40,char_rec_x,2);
  EcrireTexte(50,750,"Choisissez le nombre de lignes :",2);
  EcrireTexte(placement_x_moins+80,placement_y_recy+40,char_rec_y,2);

  /*On reste dans le menu d'avant-partie tant que le joueur n'a pas choisi d'image et n'a pas cliqué sur le bouton play*/
  for(;flag==0;){

    /*On regarde si le clique gauche a été enfoncé et si oui, où*/
    clique=SourisCliquee();
    if (clique==1){
      x=_X;
      y=_Y;
    }

    /*On rentre dans le bloc si il y a eu un clique*/
    if (clique==1){

      /*Le joueur a sélectionné la première image*/
      if (((x>=placement_x)&&(x<=placement_x+l))&&((y>=placement_y)&&(y<=placement_y+h))){
        if (premier_image_select==0){
          Encadre2(place_image[(*id_image)-1],placement_y,l,h,couleur_fond,6);
        }
        else{
          premier_image_select=0;
        }
        *id_image=1;
        Encadre2(place_image[(*id_image)-1],placement_y,l,h,color_blue,6);
        id_image_selected=1;
      }

      /*Le joueur a sélectionné la deuxième image*/
      if (((x>=placement_x+l+100)&&(x<=placement_x+l*2+100))&&((y>=placement_y)&&(y<=placement_y+h))){
        if (premier_image_select==0){
          Encadre2(place_image[(*id_image)-1],placement_y,l,h,couleur_fond,6);
        }
        else{
          premier_image_select=0;
        }
        *id_image=2;
        Encadre2(place_image[(*id_image)-1],placement_y,l,h,color_blue,6);
        id_image_selected=1;
      }

      /*Le joueur a sélectionné la troisième image*/
      if (((x>=placement_x+l*2+200)&&(x<=placement_x+l*3+200))&&((y>=placement_y)&&(y<=placement_y+h))){
        /*image3*/
        if (premier_image_select==0){
          Encadre2(place_image[(*id_image)-1],placement_y,l,h,couleur_fond,6);
        }
        else{
          premier_image_select=0;
        }
        *id_image=3;
        Encadre2(place_image[(*id_image)-1],placement_y,l,h,color_blue,6);
        id_image_selected=1;
      }

      /*Le joueur a cliqué sur le bouton Cheat. On fonction de si le bouton était déjà sélectionné ou non, on le sélectionne ou non*/
      if (((x>=1400)&&(x<=1527))&&((y>=700)&&(y<=750))){
        if (*triche==0){
          Encadre2(1400,700,127,50,color_blue,6);
          *triche=1;
        }
        else{
          Encadre2(1400,700,127,50,couleur_fond,6);
          *triche=0;
        }
      }

      /*Si on n'a pas atteint le minimum de colonnes, on en enlève une*/
      if ((*rec_x>3)&&((x>=placement_x_moins)&&(x<=placement_x_moins+50))&&((y>=placement_y_recx)&&(y<=placement_y_recx+50))){
        *rec_x=*rec_x-1;
        ChoisirCouleurDessin(couleur_fond);
        RemplirRectangle(placement_x_moins+60,placement_y_recx,80,50);
        char_rec_x[0]=(*rec_x)+'0';
        ChoisirCouleurDessin(color_black);
        EcrireTexte(placement_x_moins+80,placement_y_recx+40,char_rec_x,2);
      }

      /*Si on n'a pas atteint le maximimum de colonnes, on en rajoute une*/
      if ((*rec_x<8)&&((x>=placement_x_plus)&&(x<=placement_x_plus+50))&&((y>=placement_y_recx)&&(y<=placement_y_recx+50))){
        *rec_x=*rec_x+1;
        ChoisirCouleurDessin(couleur_fond);
        RemplirRectangle(placement_x_moins+60,placement_y_recx,80,50);
        char_rec_x[0]=(*rec_x)+'0';
        ChoisirCouleurDessin(color_black);
        EcrireTexte(placement_x_moins+80,placement_y_recx+40,char_rec_x,2);
      }

      /*Si on n'a pas atteint le minimum de lignes, on en enlève une*/
      if ((*rec_y>3)&&((x>=placement_x_moins)&&(x<=placement_x_moins+50))&&((y>=placement_y_recy)&&(y<=placement_y_recy+50))){
        *rec_y=*rec_y-1;
        ChoisirCouleurDessin(couleur_fond);
        RemplirRectangle(placement_x_moins+60,placement_y_recy,80,50);
        char_rec_y[0]=(*rec_y)+'0';
        ChoisirCouleurDessin(color_black);
        EcrireTexte(placement_x_moins+80,placement_y_recy+40,char_rec_y,2);
      }

      /*Si on n'a pas atteint le maximimum de lignes, on en rajoute une*/
      if ((*rec_y<8)&&((x>=placement_x_plus)&&(x<=placement_x_plus+50))&&((y>=placement_y_recy)&&(y<=placement_y_recy+50))){
        *rec_y=*rec_y+1;
        ChoisirCouleurDessin(couleur_fond);
        RemplirRectangle(placement_x_moins+60,placement_y_recy,80,50);
        char_rec_y[0]=(*rec_y)+'0';
        ChoisirCouleurDessin(color_black);
        EcrireTexte(placement_x_moins+80,placement_y_recy+40,char_rec_y,2);
      }

      /*Si une image a été sélectionnée, on signale au programme qu'il faut sortir du menu d'avant-partie*/
      if ((id_image_selected==1)&&(((x>=700)&&(x<=900))&&((y>=900)&&(y<=951)))){
        flag=1;
      }
    }

  }
}

/*Fonction pour encadrer*/
void Encadre2 (int x, int y,int l,int h, couleur color, int epaisseur){
  int i;
  ChoisirCouleurDessin(color);
  for (i=1;i<epaisseur;i++){
    DessinerRectangle(x-i,y-i,l+i*2-1,h+i*2-1);
  }
}
