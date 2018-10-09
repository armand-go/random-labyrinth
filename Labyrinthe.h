#ifndef LABYRINTHE_H_INCLUDED
#define LABYRINTHE_H_INCLUDED

struct Case{

/*
On cr�� un objet case, cet objet contient les valeurs des
4 c�t�s repr�sentant la case, plus un bool�en qui est vrai si la
case est d�j� visit�e.

Lors de l'initialisation, tous les c�t�s de la case valent 1.
Si un c�t� vaut 1, alors ce c�t� contient un mur
Si un c�t� vaut 2, alors ce c�t� contient un mur "indestructible"
(Ce sont les bords du labyrinthe)
Sinon, si un c�t� vaut 0, alors ce c�t� est un passage


*/

// Les c�t�s de la case
int haut;
int bas;
int gauche;
int droite;

// Bool�en si la case a �t� visit�e
int caseVisite;

};

int** allocationMemoire(int x, int y);
void freeMemoire(int x, struct Case ** Laby);

#endif // LABYRINTHE_H_INCLUDED
