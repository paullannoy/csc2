#include "coordonnees_plateau.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int coordonnees_etre_dans_plateau(int x,int y)
{
    if((x>=0 && x<NBR_CASES) && (y>=0 && y<NBR_CASES))
        return 1;
    return 0;
}

int coordonnees_etre_bordure_plateau(int x,int y)
{
    if(x == 0 || x == NBR_CASES-1 || y == 0 || y == NBR_CASES-1) // si la coordonne est sur la bordure (4 possibilités)
        return 1;

    return 0;
}

void test_coordonnees_etre_bordure_plateau(void)
{
    puts("Test coordonnees_etre_bordure_plateau \n");
    if(coordonnees_etre_bordure_plateau(0,2) != 1)
        puts("0 2 KO \n");
    if(coordonnees_etre_bordure_plateau(1,1) != 0)
        puts("1 1 KO \n");
    if(coordonnees_etre_bordure_plateau(3,4) != 1)
        puts("3 4 KO \n");
}

void coordonnees_appliquer_deplacement(int* x,int* y,orientation_deplacement orientation)
{
    assert(x!=NULL);
    assert(y!=NULL);
    assert(orientation_etre_integre_deplacement(orientation));

    // Table de correspondance:
    //  haut   -> (x,y+1)
    //  bas    -> (x,y-1)
    //  gauche -> (x-1,y)
    //  droite -> (x+1,y)

    switch(orientation)
    {
    case haut:
        *y+=1;
        break;
    case bas:
        *y-=1;
        break;
    case gauche:
        *x-=1;
        break;
    case droite:
        *x+=1;
        break;
    default:
        printf("Probleme fonction %s\n",__FUNCTION__);
    }
}





