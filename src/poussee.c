#include "poussee.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>




int poussee_etre_valide(plateau_siam* plateau,int x, int y, orientation_deplacement orientation)
{
    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));
    assert(piece_etre_integre(&(plateau->piece[x][y]) ) );
    assert(orientation_etre_integre_deplacement(orientation));


    if(poussee_calculer_force(plateau,x,y,orientation) > 0)
        return 1;

    return 0;

}

void poussee_realiser(plateau_siam* plateau,int x, int y, orientation_deplacement orientation, type_piece type, coup_jeu* coup)
{
    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));
    assert(piece_etre_case_vide(&(plateau->piece[x][y])) != 1);
    assert(piece_etre_integre(&(plateau->piece[x][y])));
    assert(orientation_etre_integre_deplacement(orientation));
    assert(coup != NULL);

    int longueur=poussee_calculer_longueur(plateau,x,y,orientation);
    int x1=0;
    int y1=0;

    if(poussee_etre_valide(plateau,x,y,orientation))
    {
        if(orientation==haut)
        {
            y1=y+longueur-1;
            if(y1==NBR_CASES && plateau->piece[x][NBR_CASES-1].type==rocher)
            {
                coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            }
            while( y1>=y )
            {
               plateau->piece[x][y1]=plateau->piece[x][y1-1];
               y1--;
            }
        }
        if(orientation==bas)
        {
            y1=y-longueur+1;
            if(y1==0 && plateau->piece[x][0].type==rocher)
            {
                coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            }
            while( y1>=y )
            {
               piece_definir(&(plateau->piece[x][y1]),plateau->piece[x][y1+1].type,plateau->piece[x][y1+1].orientation);
               y1++;
            }
        }
        if(orientation==gauche)
        {
            x1=x-longueur+1;
            if(x1==0 && plateau->piece[0][y].type==rocher)
            {
                coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            }
            while( x1>=x )
            {
               plateau->piece[x1][y]=plateau->piece[x1+1][y];
               x1++;
            }
        }
        if(orientation==droite)
        {
            x1=x-longueur+1;
            if(x1==NBR_CASES-1 && plateau->piece[NBR_CASES-1][y].type==rocher)
            {
                coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            }
            while( x1>=x )
            {
               plateau->piece[x1][y]=plateau->piece[x1-1][y];
               x1--;
            }
        }

    }
}

int poussee_calculer_longueur(plateau_siam* plateau, int x, int y, orientation_deplacement orientation)
{
    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));
    assert(piece_etre_integre(&(plateau->piece[x][y]) ) );
    assert(orientation_etre_integre_deplacement(orientation));

    int longueur = 0;
    piece_siam* piece = plateau_obtenir_piece(plateau,x,y);

    if(orientation == haut)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            longueur++;
            y++;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    if(orientation == bas)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            longueur++;
            y--;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    if(orientation == gauche)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            longueur++;
            x--;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    if(orientation == droite)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            longueur++;
            x++;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    return longueur;
}

int poussee_calculer_force(plateau_siam* plateau, int x, int y, orientation_deplacement orientation)
{
    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));
    assert(piece_etre_integre(&(plateau->piece[x][y]) ) );
    assert(orientation_etre_integre_deplacement(orientation));

    piece_siam* piece = plateau_obtenir_piece(plateau,x,y);
    int force = 1;
    int cptrocher = 0;


    if(orientation == haut)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            if(piece->orientation == orientation_inverser(orientation))
                force = force -1;

            if(piece->orientation == orientation)
                force = force +1;
            if(piece_etre_rocher(piece) == 1)
                cptrocher = cptrocher +1;
            y++;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    if(orientation == bas)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            if(piece->orientation == orientation_inverser(orientation))
                force = force -1;

            if(piece->orientation == orientation)
                force = force +1;
            if(piece_etre_rocher(piece) == 1)
                cptrocher = cptrocher +1;
            y--;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    if(orientation == gauche)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            if(piece->orientation == orientation_inverser(orientation))
                force = force -1;

            if(piece->orientation == orientation)
                force = force +1;
            if(piece_etre_rocher(piece) == 1)
                cptrocher = cptrocher +1;
            x--;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    if(orientation == droite)
    {
        while( (piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1) )
        {
            if(piece->orientation == orientation_inverser(orientation))
                force = force -1;

            if(piece->orientation == orientation)
                force = force +1;
            if(piece_etre_rocher(piece) == 1)
                cptrocher = cptrocher +1;
            x++;
            piece = plateau_obtenir_piece(plateau,x,y);
        }

    }

    if(force < cptrocher)
        force = 0;

    return force;

}
