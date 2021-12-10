/*
  La fonction "gameplay" va définir quand est-ce que le joueur a gagné (ou non)
  Sont retour va aussi être l'élément qui va potentiellement mener à la fermuture du jeu (la fonction se contenteras juste de renvoyer le retour de la fonction "win")
*/
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "gameplay.h"
#include "variables.h"
#include "win.h"

/*Fonction pour déterminer si un clique s'est produit dans un espace vide entre deux tuiles. On retourne 0 si ce n'est pas le cas et 1 si ça l'est*/
int DetectMarge (int, int, int, int, int, int);
/*Fonction pour déterminer si un clique s'est produit sur une tuile et si oui laquelle*/
void DetectCase (int, int, int, int, int*, int*, int, int);
/*Fonction pour encadrer*/
void Encadre (int, int, int, int, couleur);
/*Fonction qui gère la pré-sélection (commandes clavier). On retourne l'indice de l'emplacement sur lequel la présélection s'est déplacée*/
int PreSelect (unsigned int, int**, int, int, int, int, int, couleur, couleur, int, int, int);
/*Fonction qui intervient lors de la sélection d'une dexième tuile (pour échanger les deux tuile si l'une est vide et qu'elles sont adjacentes, pour changer la première sélection dans les autres cas)*/
void SelectDeuxiemeCase (couleur, couleur, int, int, int, int, int, int, int, int, int, int, int, int*, int*, int*, int*, int*, int*, char*,couleur,char*);

int gameplay(int** decoupe, int** position, int ordre[], int l_image, int h_image, int rec_x, int rec_y, int placement_x, int placement_y, couleur couleur_fond, couleur couleur_encadre, couleur couleur_pre_select, char* path_image){
  int flag=1,i,x,y,num_colonne,num_ligne,num_position,num_tuile,num_position2,num_tuile2,clique,touche,l_cadre,h_cadre,l_tuile,h_tuile,premier_select=1,nb_coup=0,pre_select=0,premier_pre_select=1;
  unsigned int touche_press;
  couleur color_black=CouleurParComposante(0,0,0), color_grey=CouleurParComposante(184, 186, 184);
  char char_nb_coup[4]={'0','0','0','\0'};
  /* Création du bouton "Quitter", qui se place en dessous de l'image d'origine */
  ChoisirCouleurDessin(color_grey);
  DessinerRectangle(200, 920, 100, 20);
  RemplirRectangle(200, 920, 100, 20);
  ChoisirCouleurDessin(color_black);
  EcrireTexte(205, 935, "Quitter", 0);

  l_cadre=l_image+(rec_x-1)*MARGE, h_cadre=h_image+(rec_y-1)*MARGE;
  l_tuile = l_image/rec_x, h_tuile=h_image/rec_y;

  /*Affichage du compteur de coups joués*/
  ChoisirCouleurDessin(color_black);
  EcrireTexte(1350,100,"Nombre de coups joues",1);
  EcrireTexte(1450,130,char_nb_coup,1);

  /*La boucle suivante sera exécutée tant qu'on n'est pas revenu à l'ordre normal*/
  while (flag==1){

    /*on regarde su une touche a été pressée et si oui, laquelle*/
    touche=ToucheEnAttente();
    if (touche==1){
      touche_press=Touche();
    }

    /*On regarde si un clique a eu lieux et si oui, où*/
    clique=SourisCliquee();
    if (clique==1){
      x=_X;
      y=_Y;
    }

    /*Sélection d'une première tuile via les touches clavier*/
    if ((touche==1)&&(premier_select==1)){
      /*Si la touche clavier est la barre d'espace et que la préselection est sur une tuile (pas sur la case vide), alors la tuile est sélectionée*/
      if (touche_press==XK_space){
        num_position=pre_select;
        num_tuile=ordre[num_position];
        if(num_tuile!=0){
          Encadre(position[num_position][1],position[num_position][2],l_tuile,h_tuile,couleur_encadre);
          premier_pre_select=1;
          premier_select=0;
          touche=0;
        }
      }
      /*Si la touche est une flèche directionnelle alors nous déplaçons la préselection si cela est possible (fonction PreSelect)*/
      if ((touche_press==XK_Left)||(touche_press==XK_Right)||(touche_press==XK_Up)||(touche_press==XK_Down)){
        if (premier_pre_select==1){
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
          premier_pre_select=0;
        }
        else{
          pre_select=PreSelect (touche_press,position,l_tuile,h_tuile,rec_x,rec_y,pre_select,couleur_pre_select,couleur_fond, premier_pre_select, num_position, premier_select);
          touche=0;
        }
      }
    }

    /*Sélection d'une deuxième tuile via les touches clavier*/
    if ((touche==1)&&(premier_select==0)){
      /*Si la touche clavier est la barre d'espace alors la tuile est sélectionée (fonction SelectDeuxiemeCase pour déterminer quoi faire)*/
      if (touche_press==XK_space){
        num_position2=pre_select;
        num_tuile2=ordre[num_position2];
        SelectDeuxiemeCase (couleur_fond, couleur_encadre, decoupe [num_tuile][1], decoupe [num_tuile][2], position[num_position][1], position[num_position][2], position[num_position2][1], position[num_position2][2], num_tuile2, num_position2, h_tuile, l_tuile, rec_x*rec_y, ordre, &premier_select, &nb_coup, &flag, &num_position, &num_tuile, path_image,color_black,char_nb_coup);
        premier_pre_select=1;
        if (premier_select==1){
          pre_select=0;
        }
        touche=0;
      }
      /*Si la touche est une flèche directionnelle alors nous déplaçons la préselection si cela est possible (fonction PreSelect)*/
      if ((touche_press==XK_Left)||(touche_press==XK_Right)||(touche_press==XK_Up)||(touche_press==XK_Down)){
        if (premier_pre_select==1){
          premier_pre_select=0;
        }
        pre_select=PreSelect (touche_press,position,l_tuile,h_tuile,rec_x,rec_y,pre_select,couleur_pre_select,couleur_fond, premier_pre_select, num_position, premier_select);
        touche=0;
      }
    }

    /*Sélection d'une première tuile via le clique gauche, la condition pour rentrer dans le if, est que le clique ait eu lieu dans l'encadré (invisible) qui contient les tuiles*/
    if ((clique==1)&&(premier_select==1)&&(x>=placement_x)&&(x<=placement_x+l_cadre)&&(y>=placement_y)&&(y<=placement_y+h_cadre)&&(DetectMarge(x-placement_x,y-placement_y,rec_x,rec_y,l_tuile,h_tuile)==0)){
      /*On regarde sur quelle tuile a eu lieu le clique*/
      DetectCase(x,y,placement_x,placement_y,&num_colonne,&num_ligne,l_tuile,h_tuile);
      num_position=rec_y*num_colonne+num_ligne;
      num_tuile=ordre[num_position];
      /*Comme c'est la première sélection, on ne fait quelque chose que si le clique a eu lieu sur une tuile (et non sur la case vide)*/
      if(num_tuile!=0){
        Encadre(position[num_position][1],position[num_position][2],l_tuile,h_tuile,couleur_encadre);
        premier_select=0;
        /*On regarde ici si il y avait une préselection, auquel cas il faut l'effacer, on en profite également pour placer la présélection sur la tuile sélectionnée (pour que la prochaine présélection parte de cette tuile (soucis d'érgonomie))*/
        if (premier_pre_select==0){
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
          premier_pre_select=1;
          pre_select=num_position;
        }else{
          pre_select=num_position;
        }
        clique=0;
      }
    }

    /*Sélection d'une deuxième tuile via le clique gauche (ça peut être la case vide), la condition pour rentrer dans le if, est que le clique ait eu lieu dans l'encadré (invisible) qui contient les tuiles*/
    if ((clique==1)&&(premier_select==0)&&(x>=placement_x)&&(x<=placement_x+l_cadre)&&(y>=placement_y)&&(y<=placement_y+h_cadre)&&(DetectMarge(x-placement_x,y-placement_y,rec_x,rec_y,l_tuile,h_tuile)==0)){
      /*On regarde sur quelle tuile a eu lieu le clique*/
      DetectCase(x,y,placement_x,placement_y,&num_colonne,&num_ligne,l_tuile,h_tuile);
      num_position2=rec_y*num_colonne+num_ligne;
      num_tuile2=ordre[num_position2];

      /*On appelle la fonction SelectDeuxiemeCase pour savoir ce que l'on fait suite à la seléction d'une deuxième case*/
      SelectDeuxiemeCase (couleur_fond, couleur_encadre, decoupe [num_tuile][1], decoupe [num_tuile][2], position[num_position][1], position[num_position][2], position[num_position2][1], position[num_position2][2], num_tuile2, num_position2, h_tuile, l_tuile, rec_x*rec_y, ordre, &premier_select, &nb_coup, &flag, &num_position, &num_tuile, path_image,color_black,char_nb_coup);

      /*On gère la transition entre les présélections clavier et la sélection souris en fonction des changements dans la grille*/
      if (premier_pre_select==0){
        if (premier_select==1){
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
          premier_pre_select=1;
          pre_select=0;
        }else{
          if (pre_select!=num_position){
            Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
            pre_select=num_position;
          }
        }
        premier_pre_select=1;
      }else{
          pre_select=num_position;
      }
      clique=0;
    }

    /* Sortie du jeu (bouton quitter) */
    if(clique==1 && x>=200 && x<=300 && y>=920 && y<=940){ /* Bouton "Quitter" (le jeu complet) */
      return 0;
    }
  }
  return win();
}
/*Fonction pour déterminer si un clique s'est produit dans un espace vide entre deux tuiles. On retourne 0 si ce n'est pas le cas et 1 si ça l'est*/
int DetectMarge (int x, int y, int rec_x, int rec_y, int l_tuile, int h_tuile){
  int i;
  /*On regarde si le x est à un endroit entre deux tuiles*/
  for (i=1;i<rec_x;i++){
    if ((x>=(l_tuile*i+MARGE*(i-1)))&&(x<=(l_tuile*i+MARGE*i))) {
      return 1;
    }
  }
  /*On regarde si le y est à un endroit entre deux tuiles*/
  for (i=1;i<rec_y;i++){
    if ((y>=(h_tuile*i+MARGE*(i-1)))&&(y<=(h_tuile*i+MARGE*i))) {
      return 1;
    }
  }
  return 0;
}

/*Fonction pour déterminer si un clique s'est produit sur une tuile et si oui laquelle*/
void DetectCase (int x, int y, int placement_x, int placement_y, int* num_colonne, int* num_ligne, int l_tuile, int h_tuile){
  int reste;
  /*On regarde dans quelle colonne a eu lieu le clique*/
  reste=x-placement_x,*num_colonne=0;
  for (;reste>=MARGE+l_tuile;){
    (*num_colonne)++;
    reste=reste-l_tuile;
    if (*num_colonne>0){
      reste=reste-MARGE;
    }
  }
  /*On regarde dans quelle ligne a eu lieu le clique*/
  reste=y-placement_y,*num_ligne=0;
  for (;reste>=MARGE+h_tuile;){
    (*num_ligne)++;
    reste=reste-h_tuile;
    if (*num_ligne>0){
      reste=reste-MARGE;
    }
  }
}

/*Fonction pour encadrer*/
void Encadre (int x, int y, int l, int h, couleur color){
  int i;
  /*On encadre (ici avec une épaisseur de 6 pixels)*/
  ChoisirCouleurDessin(color);
  for (i=1;i<6;i++){
    DessinerRectangle(x-i,y-i,l+i*2-1,h+i*2-1);
  }
}

/*Fonction qui gère la pré-sélection (commandes clavier). On retourne l'indice de l'emplacement sur lequel la présélection s'est déplacée*/
int PreSelect(unsigned int touche_press, int** position, int l_tuile, int h_tuile, int rec_x, int rec_y, int pre_select, couleur couleur_pre_select, couleur couleur_fond, int premier_pre_select, int num_position, int premier_select){
  /*On rentre dans le bloc si la touche enfoncée est la flèche directionnelle vers la gauche et qu'on peut déplacer la présélection d'une case vers la gauche*/
  /*On va y déplacer la présélection*/
  if ((touche_press==XK_Left)&&(pre_select>=rec_y)){
    if (((premier_pre_select==1)||(pre_select-rec_y==num_position)||(pre_select==num_position))&&(premier_select==0)){
      if (pre_select-rec_y==num_position){
        Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
        pre_select=pre_select-rec_y;
      }
      else {
        if (pre_select==num_position){
          pre_select=pre_select-rec_y;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
        else{
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
          pre_select=pre_select-rec_y;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
      }
    }
    else{
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
      pre_select=pre_select-rec_y;
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
    }
    return pre_select;
  }

  /*On rentre dans le bloc si la touche enfoncée est la flèche directionnelle vers la droite et qu'on peut déplacer la présélection d'une case vers la droite*/
  /*On va y déplacer la présélection*/
  if ((touche_press==XK_Right)&&(pre_select<rec_y*(rec_x-1))){
    if (((premier_pre_select==1)||(pre_select+rec_y==num_position)||(pre_select==num_position))&&(premier_select==0)){
      if (pre_select+rec_y==num_position){
        Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
        pre_select=pre_select+rec_y;
      }
      else {
        if (pre_select==num_position){
          pre_select=pre_select+rec_y;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
        else{
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
          pre_select=pre_select+rec_y;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
      }
    }
    else{
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
      pre_select=pre_select+rec_y;
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
    }
    return pre_select;
  }

  /*On rentre dans le bloc si la touche enfoncée est la flèche directionnelle vers le haut et qu'on peut déplacer la présélection d'une case vers la haut*/
  /*On va y déplacer la présélection*/
  if ((touche_press==XK_Up)&&((pre_select%rec_y)!=0)){
    if (((premier_pre_select==1)||(pre_select-1==num_position)||(pre_select==num_position))&&(premier_select==0)){
      if (pre_select-1==num_position){
        Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
        pre_select=pre_select-1;
      }
      else {
        if (pre_select==num_position){
          pre_select=pre_select-1;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
        else{
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
          pre_select=pre_select-1;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
      }
    }
    else{
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
      pre_select=pre_select-1;
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
    }
    return pre_select;
  }

  /*On rentre dans le bloc si la touche enfoncée est la flèche directionnelle vers le bas et qu'on peut déplacer la présélection d'une case vers la bas*/
  /*On va y déplacer la présélection*/
  if ((touche_press==XK_Down)&&(((pre_select+1)%rec_y)!=0)){
    if (((premier_pre_select==1)||(pre_select+1==num_position)||(pre_select==num_position))&&(premier_select==0)){
      if (pre_select+1==num_position){
        Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
        pre_select=pre_select+1;
      }
      else {
        if (pre_select==num_position){
          pre_select=pre_select+1;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
        else{
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
          pre_select=pre_select+1;
          Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
        }
      }
    }
    else{
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_fond);
      pre_select=pre_select+1;
      Encadre(position[pre_select][1],position[pre_select][2],l_tuile,h_tuile,couleur_pre_select);
    }
    return pre_select;
  }
  return pre_select;
}

/*Fonction qui intervient lors de la sélection d'une dexième tuile (pour échanger les deux tuile si l'une est vide et qu'elles sont adjacentes, pour changer la première sélection dans les autres cas)*/
void SelectDeuxiemeCase (couleur couleur_fond, couleur couleur_encadre, int decoupe1, int decoupe2, int position1_1, int position1_2,int position2_1,int position2_2, int num_tuile2, int num_position2, int h_tuile, int l_tuile, int nb_tuile, int ordre[], int* premier_select, int* nb_coup, int* flag, int* num_position, int* num_tuile, char* path_image,couleur color_black, char* char_nb_coup){
  int i,flag2;

  /*On entre dans le bloc si la deuxième case sélectionnée est la case vide et que les deux cases sélectionnées sont adjacentes*/
  if ((num_tuile2==0)&&(((position1_1==position2_1)&&((position1_2+h_tuile+MARGE==position2_2)||(position2_2+h_tuile+MARGE==position1_2)))||((position1_2==position2_2)&&((position1_1+l_tuile+MARGE==position2_1)||(position2_1+l_tuile+MARGE==position1_1))))){

    /*On efface ce qui doit êtré effacé*/
    ChoisirCouleurDessin(couleur_fond);
    if (position1_1==position2_1){
      if (position1_2<position2_2){
        RemplirRectangle(position1_1-5,position1_2-5,l_tuile+10,h_tuile*2+MARGE+10);
      }else{
        RemplirRectangle(position2_1-5,position2_2-5,l_tuile+10,h_tuile*2+MARGE+10);
      }
    }
    else{
      if (position1_1<position2_1){
        RemplirRectangle(position1_1-5,position1_2-5,l_tuile*2+MARGE+10,h_tuile+10);
      }else{
        RemplirRectangle(position2_1-5,position2_2-5,l_tuile*2+MARGE+10,h_tuile+10);
      }
    }

    /*On change la tuile sélectionnée, de place*/
    ChargerImage(path_image,position2_1,position2_2,decoupe1,decoupe2,l_tuile,h_tuile);
    ordre[num_position2]=*num_tuile;
    ordre[*num_position]=0;

    *premier_select=1;

    /*On gère le compteur du nombre de coups joués*/
    (*nb_coup)++;
    char_nb_coup[0]=((*nb_coup)/100)+'0';
    char_nb_coup[1]=(((*nb_coup)-100*((*nb_coup)/100))/10)+'0';
    char_nb_coup[2]=((*nb_coup)-(10*(((*nb_coup)-100*((*nb_coup)/100))/10))-(100*((*nb_coup)/100)))+'0';
    ChoisirCouleurDessin(couleur_fond);
    RemplirRectangle(1400,110,100,50);
    ChoisirCouleurDessin(color_black);
    EcrireTexte(1450,130,char_nb_coup,1);

    /*On regarde si l'ordre est celui d'origine et on change (ou non) la valeur du flag en fonction durésultat (le flag dit au programme si il faut continuer à jouer ou si l'ordre a été rétabli)*/
    flag2=1;
    for (i=0;(i<nb_tuile)&&(flag2==1);i++){
      if (ordre[i]!=i){
        flag2=0;
      }
    }
    if (flag2==1){
      *flag=0;
    }
    
  }
  else {
    /* Si la deuxième case sélectionnée n'est pas la case vide alors la deuxième case sélectionnée devient la première*/
    if ((num_tuile2)!=0){
      Encadre(position1_1,position1_2,l_tuile,h_tuile,couleur_fond);
      Encadre(position2_1,position2_2,l_tuile,h_tuile,couleur_encadre);
      *num_position=num_position2;
      *num_tuile=num_tuile2;
    }
  }
}
