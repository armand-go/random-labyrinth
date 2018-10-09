#ifndef LABYRINTHE_H_INCLUDED
#define LABYRINTHE_H_INCLUDED

struct Case{

/*
On créé un objet case, cet objet contient les valeurs des
4 côtés représentant la case, plus un booléen qui est vrai si la
case est déjà visitée.

Lors de l'initialisation, tous les côtés de la case valent 1.
Si un côté vaut 1, alors ce côté contient un mur
Si un côté vaut 2, alors ce côté contient un mur "indestructible"
(Ce sont les bords du labyrinthe)
Sinon, si un côté vaut 0, alors ce côté est un passage


*/

// Les côtés de la case
int haut;
int bas;
int gauche;
int droite;

// Booléen si la case a été visitée
int caseVisite;

};

int** allocationMemoire(int x, int y);
void freeMemoire(int x, struct Case ** Laby);

#endif // LABYRINTHE_H_INCLUDED
