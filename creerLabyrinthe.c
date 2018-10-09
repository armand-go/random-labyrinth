#include "creerLabyrinthe.h"


void creerLabyrinthe(struct Case **labyrinthe, int x, int y){

    /* Deux tablaux, un qui contient l'historique des abscisses, l'autre celui des ordonnées
     dans le cas où aucune direction n'est possible, alors on revient sur nos pas
     à l'aide de ces deux tableaux */

        int *historiqueX;
        int *historiqueY;

    /* Pour l'instant, ce tableau ne contient aucune position, inutile d'allouer
        de la mémoire, mais il nous faut l'initialiser */

        historiqueX = tableauHistorique(1, 0);
        historiqueY = tableauHistorique(1, 0);

    /*
        On choisit au hasard les coordonées de la case où nous
        allons commencer à construire le labyrinthe.
    */

        srand(time(NULL));
        int xi = rand() % x;
        int yi = rand() % y;


    // Les longueurs des tableaux d'historique. Pour le moment elles sont à 0

    int longueurX = 0, longueurY = 0;

    //Tant que cette variable est vraie, il y a encore possibilité de construire.

    int construire = 1;

        /*
        Une variable booléenne qui est vraie (= 1) lorsqu'on a une
        direction dans laquelle on peut aller
        */

    int onATrouveUneDirection = 0;

    while(construire == 1){


        /* Un tableau qui contient nos directions.
        Il se réinitialise à chaque tour de boucle, c'est à dire
        à chaque fois qu'on est sur une nouvelle case */

        int *direction;
        direction = tableauHistorique(4, 0);
        int i;
        for(i = 0; i < 4; i++){
            direction[i] = i;
        }

        int directionsPossibles = 4;

        /*
        Une variable booléenne qui est vraie (= 1) lorsqu'on a une
        direction dans laquelle on peut aller
        */

        int onATrouveUneDirection = 0;

        while(onATrouveUneDirection == 0){
            // Nous sommes sur un case, on l'a alors visitée.
            printf("\nPosition actuelle : %d,%d\n", xi,yi);
            labyrinthe[xi][yi].caseVisite = 1;

            /* On créer deux nouveaux tableaux qui contiennent l'abscisse et l'ordonnée
            actuelle */

            int *actuelX, *actuelY;

            actuelX = tableauHistorique(1, xi);
            actuelY = tableauHistorique(1, yi);

            /*
                On enregistre notre position dans le cas où il faudrait revenir sur cette position
                sur la prochaine case si aucune direction n'est possible. Pour ça, on concatène
                le tableau des historiques avec le tableau des abscisses et des ordonnées
                de la nouvelle position.
            */

            historiqueX = additionTableau(historiqueX, actuelX, longueurX);
            historiqueY = additionTableau(historiqueY, actuelY, longueurY);
            longueurX += 1; // On a rajouté la position actuelle dans le tableau des historiques
            longueurY += 1; // Pareil

            /* On choisit la direction dans laquelle on va commencer à aller
            casser du mur. */

            int onVaDansCetteDirection = direction[rand() % directionsPossibles];

            printf("On va dans cette direction : %d\n", onVaDansCetteDirection);
            /* Quelque soit la direction où l'on va, on verifie qu'on est pas sur un des bords
            du labyrinthe (mur "indestructible") et que la case n'a pas déjà été visitée.
            */

                switch(onVaDansCetteDirection){

                    case HAUT:
                        if(labyrinthe[xi][yi].haut == 2 || labyrinthe[xi][yi-1].caseVisite == 1){
                            // Si il y a un mur incassable dans cette direction ou que la case a déjà été visitée :

                            printf("On ne peut pas y aller\n");

                            // On créé une copie de notre tableau de direction actuel moins la direction testée

                            direction = copieDirections(direction, directionsPossibles, HAUT);
                            directionsPossibles -= 1; // On a retiré la direction actuelle qui ne fonctionne pas
                            longueurX -= 1; // Puisqu'on ne bouge pas, on ne rajoute pas la position à l'historique, ...
                            longueurY -= 1;// ... donc sa taille ne varie pas.
                        break;
                        }
                        else{
                            // Sinon, on peut aller dans cette direction !
                            printf("On y va !\n");
                            labyrinthe[xi][yi].haut = 0; // On détruit le mur sur la case actuelle...
                            labyrinthe[xi][yi - 1].bas = 0; // ... qui est le même que sur la case adjacente.
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
                        /* Si on a testé les quatres directions et qu'aucune n'est possible,
                        alors il faut revenir en arrière */

                        xi = historiqueX[longueurX - 1]; // xi prends la valeur du dernier élement dans l'historique
                        yi = historiqueY[longueurY - 1]; // Pareil
                        printf("On retourne a la case precedente c'est a dire %d,%d\n", xi, yi);

                        /* On regarde si cette position n'est pas celle de départ. Si c'est le cas,
                        on a fini de constuire le labyrinthe, donc on sort de la boucle de construction */

                        if(xi == historiqueX[0] && yi == historiqueY[0]){
                            construire = 0; // On arrête la construction, on a fini
                            printf("On a fini la construction !!");
                        }

                        /* Il faut supprimer la position qui n'a pas marchée de l'historique pour
                        ne pas revenir dessus si la nouvelle position ne marche pas.
                        On supprimer également la nouvelle position de l'historique puisqu'on va la
                        réaffecter avec le nouveau tour de boucle */

                        historiqueX = soustractionHistorique(historiqueX, longueurX);
                        historiqueY = soustractionHistorique(historiqueY, longueurY);
                        longueurX -= 1;
                        longueurY -= 1;


                        /* Même si c'est pas tellement vrai mais il faut sortir de la boucle
                        On sait où on va : en arrière */

                        onATrouveUneDirection = 1;
                    }

                    /* On libère les tableaux avec les anciennes positions */
                    free(actuelX);
                    free(actuelY);
                }
                free(direction);
            }

    /* On libère la mémoire allouée pour les différents tableau d'historique. */
    free(historiqueX);
    free(historiqueY);

    return labyrinthe;
}

int copieDirections(int *directions, int directionsPossibles, int DIRECTION){
    /* Fonction qui va copier les directions dans un nouveau tableau en retirant
    celle qu'on vient de tester, car cette fonction est appellée lorsqu'on ne peut
    pas se déplacer dans une direction testée */

    int *directionCopie;

    printf("On supprime la direction %d car elle n'est pas possible\n\n", DIRECTION);

    // On créé une copie de notre tableau de direction actuel de dimension n - 1

    directionCopie = malloc((directionsPossibles - 1) * sizeof(*directionCopie));
    if(directionCopie == NULL){
        return -1;
    }

        /*
            Puis on réaffecte les différentes diretions dans la copie sauf la direction que
            l'on a déjà essayée
        */
        int i, j = 0;
        for(i = 0; i < directionsPossibles; i++, j++){
            if(directions[i] != DIRECTION){
                directionCopie[j] = directions[i]; // On affecte la drection si ce n'est pas celle qui ne fonctionne pas
            }
            else{ // Sinon, c'est celle qui ne marche pas
                j -= 1; // On n'incremente pas notre tableau copié
            }
        }
    return directionCopie;
}

int* tableauHistorique(int x, int xi){

    /* Fonction qui va créer le tableau contenant l'historique des abscisses ou des ordonnées.
    On préfère faire un tableau pour les abscisses et un pour les ordonnées pour faciliter
    le parcours des positions.
    Il recoit en paramètre la taille du tableau ainsi que la valeur de la position actuelle.
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

    // On déclare le nouveau tableau

    int *nouveauTableau;

    /* Il faut connaître la taille qu'on a besoin d'allouer.
    Petit calcul ici :
        On veut allouer x cases en mémoire. (Le tableau historique plus le tableau actuel)
        La fonction malloc a besoin du nombre de cases qu'on veut allouer. Donc x.
        Il n'existe pas de fonction en C pour récupérer la longueur brut d'un tableau.
        Toutefois, si on fait sizeof(historique + actuel), on aura la taille que
        prennent les deux tableaux. Il suffit de divisier par la taille du type (ici int)
        pour obtenir la longueur du tableau voulu !
        Ainsi :
    */

    nouveauTableau = malloc((longueurHistorique + 1) * sizeof(*nouveauTableau));
    if(nouveauTableau == NULL){
        return -1;
    }

    /* On parcourt à présent notre historique actuel et on le copie dans
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

    /* Fonction qui va retirer les deux dernières position du tableau
    des historiques */

    // On déclare un nouveau tableau d'historique
    int *nouvelHistorique;

    /* Sa taille sera de tailleHistorique - 2 car on veut enlever la dernière position qui
    n'a pas donnée de résultat et l'avant dernière position, qui est celle sur laquelle
    on se trouve a présent, car elle va être de nouveau rajoutée lors du prochain tour de boucle
    */
    nouvelHistorique = malloc((tailleHistorique - 1) * sizeof(*nouvelHistorique));
    if(nouvelHistorique == NULL){
        return -1;
    }

    /* On affecte à présent le tableau des historiques actuel moins les deux dernières
    valeurs au nouvel historique */
    int i;
    for(i = 0; i < (tailleHistorique - 1); i++){
        nouvelHistorique[i] = historique[i];
    }

    return nouvelHistorique;
}
