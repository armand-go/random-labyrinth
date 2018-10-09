#ifndef CREERLABYRINTHE_H_INCLUDED
#define CREERLABYRINTHE_H_INCLUDED

enum {HAUT, BAS, GAUCHE, DROITE};

int copieDirections(int *directions, int directionsPossibles, int DIRECTION);
int* tableauHistorique(int x, int xi);
int* additionTableau(int *historique, int *actuel, int longueurHistorique);
int* soustractionHistorique(int *historique, int tailleHistorique);

#endif // CREERLABYRINTHE_H_INCLUDED
