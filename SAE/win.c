#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>


int win(){
    /* Le joueur a gagné */
    ChargerImageFond(PATH_WIN); /* Image de fond */
    couleur c;
    c = CouleurParComposante(234, 50, 37); /* Rouge */
    ChoisirCouleurDessin(c);
    DessinerRectangle(1200, 500, 100, 20); /* Bouton quitter */
    RemplirRectangle(1200, 500, 100, 20); /* Bouton quitter */
    c = CouleurParComposante(15, 211, 56); /* Vert */
    ChoisirCouleurDessin(c);
    DessinerRectangle(200, 500, 100, 20); /* Bouton Rejouer */
    RemplirRectangle(200, 500, 100, 20); /* Bouton Rejouer */
    c = CouleurParComposante(0, 0, 0);
    ChoisirCouleurDessin(c);
    EcrireTexte(1205, 515, "Quitter", 0);
    EcrireTexte(205, 515, "Rejouer", 0);
    while (1) { /* Attente de l'event "QQ1 Clic" */
        if(SourisCliquee()){
            if(_X>=1200 &&  _X <= 1300 && _Y>=500 && _Y<520){
                /* L'utilisateur veut quitter le jeu */
                return 0;
            }
            if(_X >= 200 && _X <= 300 && _Y >= 500 && _Y<=520){
                /* L'utilisateur veut rejouer */
                return 2;
            }
        }
    }
}
