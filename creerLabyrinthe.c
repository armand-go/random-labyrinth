#include "creerLabyrinthe.h"


void creerLabyrinthe(struct Case **labyrinthe, int x, int y){

    /* Deux tablaux, un qui contient l'historique des abscisses, l'autre celui des ordonn�es
     dans le cas o� aucune direction n'est possible, alors on revient sur nos pas
     � l'aide de ces deux tableaux */

        int *historiqueX;
        int *historiqueY;

    /* Pour l'instant, ce tableau ne contient aucune position, inutile d'allouer
        de la m�moire, mais il nous faut l'initialiser */

        historiqueX = tableauHistorique(1, 0);
        historiqueY = tableauHistorique(1, 0);

    /*
        On choisit au hasard les coordon�es de la case o� nous
        allons commencer � construire le labyrinthe.
    */

        srand(time(NULL));
        int xi = rand() % x;
        int yi = rand() % y;


    // Les longueurs des tableaux d'historique. Pour le moment elles sont � 0

    int longueurX = 0, longueurY = 0;

    //Tant que cette variable est vraie, il y a encore possibilit� de construire.

    int construire = 1;

        /*
        Une variable bool�enne qui est vraie (= 1) lorsqu'on a une
        direction dans laquelle on peut aller
        */

    int onATrouveUneDirection = 0;

    while(construire == 1){


        /* Un tableau qui contient nos directions.
        Il se r�initialise � chaque tour de boucle, c'est � dire
        � chaque fois qu'on est sur une nouvelle case */

        int *direction;
        direction = tableauHistorique(4, 0);
        int i;
        for(i = 0; i < 4; i++){
            direction[i] = i;
        }

        int directionsPossibles = 4;

        /*
        Une variable bool�enne qui est vraie (= 1) lorsqu'on a une
        direction dans laquelle on peut aller
        */

        int onATrouveUneDirection = 0;

        while(onATrouveUneDirection == 0){
            // Nous sommes sur un case, on l'a alors visit�e.
            printf("\nPosition actuelle : %d,%d\n", xi,yi);
            labyrinthe[xi][yi].caseVisite = 1;

            /* On cr�er deux nouveaux tableaux qui contiennent l'abscisse et l'ordonn�e
            actuelle */

            int *actuelX, *actuelY;

            actuelX = tableauHistorique(1, xi);
            actuelY = tableauHistorique(1, yi);

            /*
                On enregistre notre position dans le cas o� il faudrait revenir sur cette position
                sur la prochaine case si aucune direction n'est possible. Pour �a, on concat�ne
                le tableau des historiques avec le tableau des abscisses et des ordonn�es
                de la nouvelle position.
            */

            historiqueX = additionTableau(historiqueX, actuelX, longueurX);
            historiqueY = additionTableau(historiqueY, actuelY, longueurY);
            longueurX += 1; // On a rajout� la position actuelle dans le tableau des historiques
            longueurY += 1; // Pareil

            /* On choisit la direction dans laquelle on va commencer � aller
            casser du mur. */

            int onVaDansCetteDirection = direction[rand() % directionsPossibles];

            printf("On va dans cette direction : %d\n", onVaDansCetteDirection);
            /* Quelque soit la direction o� l'on va, on verifie qu'on est pas sur un des bords
            du labyrinthe (mur "indestructible") et que la case n'a pas d�j� �t� visit�e.
            */

                switch(onVaDansCetteDirection){

                    case HAUT:
                        if(labyrinthe[xi][yi].haut == 2 || labyrinthe[xi][yi-1].caseVisite == 1){
                            // Si il y a un mur incassable dans cette direction ou que la case a d�j� �t� visit�e :

                            printf("On ne peut pas y aller\n");

                            // On cr�� une copie de notre tableau de direction actuel moins la direction test�e

                            direction = copieDirections(direction, directionsPossibles, HAUT);
                            directionsPossibles -= 1; // On a retir� la direction actuelle qui ne fonctionne pas
                            longueurX -= 1; // Puisqu'on ne bouge pas, on ne rajoute pas la position � l'historique, ...
                            longueurY -= 1;// ... donc sa taille ne varie pas.
                        break;
                        }
                        else{
                            // Sinon, on peut aller dans cette direction !
                            printf("On y va !\n");
                            labyrinthe[xi][yi].haut = 0; // On d�truit le mur sur la case actuelle...
                            labyrinthe[xi][yi - 1].bas = 0; // ... qui est le m�me que sur la case adjacente.
                            yi -= 1; // On se place sur la nouvelle case
                            onATrouveUneDirection = 1; // Bah oui. :D Il faut sortir de la boucle si on a une direction
                            printf("Longueur x = %d\n", longueurX);
                        break;
                        }

                    case BAS:
                        if(labyrinthe[xi][yi].bas == 2 || labyrinthe[xi][yi+1].caseVisite == 1){

                            printf("On ne peut pas y aller\n");
                            direction = copieDirections(direction, directionsPossibles, BAS);
                            directionsPossibles -= 1;
                            longueurX -= 1;
                            longueurY -= 1;
                        break;
                        }
                        else{
                            printf("On y va !\n\n");
                            labyrinthe[xi][yi].bas = 0;
                            labyrinthe[xi][yi + 1].haut = 0;
                            yi += 1;
                            onATrouveUneDirection = 1;
                            printf("Longueur x = %d\n", longueurX);
                        break;
                        }

                    case DROITE:
                        if(labyrinthe[xi][yi].droite == 2 || labyrinthe[xi+1][yi].caseVisite == 1){

                            printf("On ne peut pas y aller\n");
                            direction = copieDirections(direction, directionsPossibles, DROITE);
                            directionsPossibles -= 1;
                            longueurX -= 1;
                            longueurY -= 1;
                        break;
                        }
                        else{
                            printf("On y va !\n\n");
                            labyrinthe[xi][yi].droite = 0;
                            labyrinthe[xi+1][yi].gauche = 0;
                            xi += 1;
                            onATrouveUneDirection = 1;
                            printf("Longueur x = %d\n", longueurX);
                        break;
                        }

                    case GAUCHE:
                        if(labyrinthe[xi][yi].gauche == 2 || labyrinthe[xi - 1][yi].caseVisite == 1){

                            printf("On ne peut pas y aller\n");
                            direction = copieDirections(direction, directionsPossibles, GAUCHE);
                            directionsPossibles -= 1;
                            longueurX -= 1;
                            longueurY -= 1;
                        break;
                        }
                        else{
                            printf("On y va !\n");
                            labyrinthe[xi][yi].gauche = 0;
                            labyrinthe[xi - 1][yi].droite = 0;
                            xi -= 1;
                            onATrouveUneDirection = 1;
                            printf("Longueur x = %d\n", longueurX);
                        break;
                        }

                    }

                    if(directionsPossibles == 0){
                        /* Si on a test� les quatres directions et qu'aucune n'est possible,
                        alors il faut revenir en arri�re */

                        xi = historiqueX[longueurX - 1]; // xi prends la valeur du dernier �lement dans l'historique
                        yi = historiqueY[longueurY - 1]; // Pareil
                        printf("On retourne a la case precedente c'est a dire %d,%d\n", xi, yi);

                        /* On regarde si cette position n'est pas celle de d�part. Si c'est le cas,
                        on a fini de constuire le labyrinthe, donc on sort de la boucle de construction */

                        if(xi == historiqueX[0] && yi == historiqueY[0]){
                            construire = 0; // On arr�te la construction, on a fini
                            printf("On a fini la construction !!");
                        }

                        /* Il faut supprimer la position qui n'a pas march�e de l'historique pour
                        ne pas revenir dessus si la nouvelle position ne marche pas.
                        On supprimer �galement la nouvelle position de l'historique puisqu'on va la
                        r�affecter avec le nouveau tour de boucle */

                        historiqueX = soustractionHistorique(historiqueX, longueurX);
                        historiqueY = soustractionHistorique(historiqueY, longueurY);
                        longueurX -= 1;
                        longueurY -= 1;


                        /* M�me si c'est pas tellement vrai mais il faut sortir de la boucle
                        On sait o� on va : en arri�re */

                        onATrouveUneDirection = 1;
                    }

                    /* On lib�re les tableaux avec les anciennes positions */
                    free(actuelX);
                    free(actuelY);
                }
                free(direction);
            }

    /* On lib�re la m�moire allou�e pour les diff�rents tableau d'historique. */
    free(historiqueX);
    free(historiqueY);

    return labyrinthe;
}

int copieDirections(int *directions, int directionsPossibles, int DIRECTION){
    /* Fonction qui va copier les directions dans un nouveau tableau en retirant
    celle qu'on vient de tester, car cette fonction est appell�e lorsqu'on ne peut
    pas se d�placer dans une direction test�e */

    int *directionCopie;

    printf("On supprime la direction %d car elle n'est pas possible\n\n", DIRECTION);

    // On cr�� une copie de notre tableau de direction actuel de dimension n - 1

    directionCopie = malloc((directionsPossibles - 1) * sizeof(*directionCopie));
    if(directionCopie == NULL){
        return -1;
    }

        /*
            Puis on r�affecte les diff�rentes diretions dans la copie sauf la direction que
            l'on a d�j� essay�e
        */
        int i, j = 0;
        for(i = 0; i < directionsPossibles; i++, j++){
            if(directions[i] != DIRECTION){
                directionCopie[j] = directions[i]; // On affecte la drection si ce n'est pas celle qui ne fonctionne pas
            }
            else{ // Sinon, c'est celle qui ne marche pas
                j -= 1; // On n'incremente pas notre tableau copi�
            }
        }
    return directionCopie;
}

int* tableauHistorique(int x, int xi){

    /* Fonction qui va cr�er le tableau contenant l'historique des abscisses ou des ordonn�es.
    On pr�f�re faire un tableau pour les abscisses et un pour les ordonn�es pour faciliter
    le parcours des positions.
    Il recoit en param�tre la taille du tableau ainsi que la valeur de la position actuelle.
    */

    int i;
    int *historique;
    historique = malloc(x * sizeof(*historique));
    if(historique == NULL){
        return -1;
    }
    for(i = 0; i < x; i++){
        historique[i] = xi;
    }
    return historique;
}

int* additionTableau(int *historique, int *actuel, int longueurHistorique){

    // On d�clare le nouveau tableau

    int *nouveauTableau;

    /* Il faut conna�tre la taille qu'on a besoin d'allouer.
    Petit calcul ici :
        On veut allouer x cases en m�moire. (Le tableau historique plus le tableau actuel)
        La fonction malloc a besoin du nombre de cases qu'on veut allouer. Donc x.
        Il n'existe pas de fonction en C pour r�cup�rer la longueur brut d'un tableau.
        Toutefois, si on fait sizeof(historique + actuel), on aura la taille que
        prennent les deux tableaux. Il suffit de divisier par la taille du type (ici int)
        pour obtenir la longueur du tableau voulu !
        Ainsi :
    */

    nouveauTableau = malloc((longueurHistorique + 1) * sizeof(*nouveauTableau));
    if(nouveauTableau == NULL){
        return -1;
    }

    /* On parcourt � pr�sent notre historique actuel et on le copie dans
    le nouveau tableau. On ajoute ensuite la position actuelle
    */

    int i;
    for(i = 0; i < longueurHistorique; i++){
        nouveauTableau[i] = historique[i];
    }
    nouveauTableau[i] = actuel[0];

    return nouveauTableau;
}

int* soustractionHistorique(int *historique, int tailleHistorique){

    /* Fonction qui va retirer les deux derni�res position du tableau
    des historiques */

    // On d�clare un nouveau tableau d'historique
    int *nouvelHistorique;

    /* Sa taille sera de tailleHistorique - 2 car on veut enlever la derni�re position qui
    n'a pas donn�e de r�sultat et l'avant derni�re position, qui est celle sur laquelle
    on se trouve a pr�sent, car elle va �tre de nouveau rajout�e lors du prochain tour de boucle
    */
    nouvelHistorique = malloc((tailleHistorique - 1) * sizeof(*nouvelHistorique));
    if(nouvelHistorique == NULL){
        return -1;
    }

    /* On affecte � pr�sent le tableau des historiques actuel moins les deux derni�res
    valeurs au nouvel historique */
    int i;
    for(i = 0; i < (tailleHistorique - 1); i++){
        nouvelHistorique[i] = historique[i];
    }

    return nouvelHistorique;
}
