#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Labyrinthe.h"
#include "creerLabyrinthe.c"


int main()
{
    // i et j sont les variables qui serviront à incrémenter nos boucles
    int i, j;

    // x et y sont l'abscisse et l'ordonnée maximale d'une case du labyrinthe
    int x, y;
	x = 5; y = 5;
    // On alloue la mémoire nécessaire pour la création du labyrinthe
    // Ce labyrinthe aura x cases en abscisse et y case en ordonnées
    struct Case **labyrinthe = allocationMemoire(x, y);

	// On créé un case "type"
	struct Case maCase;
	maCase.haut = 1;
	maCase.bas = 1;
	maCase.gauche = 1;
	maCase.droite = 1;
	maCase.caseVisite = 0;

	// On affecte à chaque case du labyrinthe la valeur de la case type
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			labyrinthe[i][j] = maCase;
		}
	}

	/*
	On change la valeurs des murs définnissant les bords du labyrinthe
	afin d'en faire des murs indestructibles.
	*/
	for(i = 0; i < x; i++){ // Les bords du haut et du bas
        labyrinthe[i][0].haut = 2;
        labyrinthe[i][y-1].bas = 2;
        }

	for(j = 0; j < y; j++){ // Les bords de droite et de gauche
        labyrinthe[0][j].gauche = 2;
        labyrinthe[x-1][j].droite = 2;
	}

	/*
	A partir d'ici, le labyrinthe est correctement initialisé. Il est de 20x20 cases.
	Les bords, sont "indestructibles", on ne pourra pas les modifier par erreur.
	Pour le moment, chaque case est doté de 4 murs. On a donc en fait un quadrillage.
	*/

    // On va véritablement créer le labyrinthe grâce à la fonction suivante
    creerLabyrinthe(labyrinthe, x, y); // Labyrinthe est une adresse ici, on peut donc envoyer les deux dimensions !

    /*
    Avant de fermer le programme, on libère la mémoire allouée
    pour le labyrinthe. Histoire que mon ordinateur ne plante pas ;)
    */
    freeMemoire(x, labyrinthe);
    return 0;
}

int** allocationMemoire(int x, int y){
    /*
        Fonction qui créée notre tableau en mémoire.
        On passe par une allocation dynamique car s'il faut modifier notre
        tableau à deux entrées, il n'est pas possible de l'envoyer directement en argument
        à une fonction puisqu'il a plusieurs dimensions, dynamiques qui plus est.
        Tandis que si on travaille avec l'adresse, le problème ne se pose plus.
    */

    struct Case **Laby;
    /* Cette variable est un double pointeur (un pointeur sur chaque dimension de notre labyrinthe)
    Il contiendra l'adresse de notre labyrinthe que l'on retournera.
    Il est du type Case, puisque notre tableau est un tableau de Case.
    */
    int i;

    Laby = malloc(x * sizeof(*Laby));
    if(Laby == NULL){
        return -1;
        }

    for(i = 0; i < x; i++){
        Laby[i] = malloc(y * sizeof(**Laby));
        if(Laby[i] == NULL){
            return -1;
        }
    }
    return Laby;
}

void freeMemoire(int x, struct Case ** Laby){
    int i;
    for(i=0; i < x; i++){
        free(Laby[i]);
    }
    free(Laby);
}
