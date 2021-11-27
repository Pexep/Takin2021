/*
    Quels explications sur l'utilité des constantes et variables :
     x = Indice de colone (n° tuile)
     z = Indice de ligne (n° ligne)
     l = valeur étalon (La longueur d'une tuile)
     h = valeur étalon (La hauteur d'une tuile)
     l_image = Longueurs maximal de l'image
     h_image = Hauteur maximal de l'image
     marge = Les marges a appliquer
     rec = Le nombre de colones à faire
     PATH = Le lien vers le fichier (défini dans le .h)
*/
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "affichage.h"


int affichage(int l_image, int h_image, int marge, int rec){
    int l, h, x=0, z=0; /* Valeurs de base */

    /* Définition de la taille de la fenêtre, elle doit être assez grande pour contenir tout les fragements, c'est pour ça que ça taile évolue en fonction des marges et du
    nombre de colones (REC). Je retire une fois la valeur d'une marge pour réduire un peu la fenêtre */
    l = l_image/rec, h=h_image/rec; /* Calcul des valeurs étalons pour la taile des tuiles */
    while (x!=rec) { /* Cette boucle doit s'éxecuter tant que le nombre de colones demandé n'a pas été généré */
        if(z%rec!=0 || z==0){ /* Vu que la valeur 0 est importante pour le placement des images, je rajoute une clause spécial dédié à si z=0, autrement, cette condition est
          vérifié tant que le numéro de tuile (z) ne correspond pas au nombre de colones à faire (REC) */
            ChargerImage(PATH, (z*marge)+(z*l), (x*marge)+(x*h), z*l, x*h, l, h); /* Placement des fragements d'images - Les positions doivent tenir comptes des marges a
            appliquer et aussi de la taile d'une tuile. Pour que la tuile affiché soit la bonne, le programme utilise le compteur "n° tuile" (z) ainsi que "n° ligne (h)" */
            printf("%d - %d - %d - %d - %d\n", (z*marge)+(z*l), (x*marge)+(x*h), z*l, x*h, z); /* Debug values - Useless */
            z++; /* Mise à jour du compteur tuile */
        }else{
            z=0, x++; /* Mise à jour des compteurs tuile et colone */
        }
    }
    return EXIT_SUCCESS;
}
