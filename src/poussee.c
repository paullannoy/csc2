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

    piece_siam* piece = plateau_obtenir_piece(plateau,x,y);

    if(  piece_etre_case_vide( &(plateau->piece[x][y]) ) == 1 )
        return 0;

    if(orientation == haut)
    {
        piece = plateau_obtenir_piece(plateau,x,y-1);
        if(piece->orientation != orientation)
            return 0;
    }
    if(orientation == bas)
    {
        if(plateau->piece[x][y+1].orientation != orientation)
            return 0;
    }
    if(orientation == gauche)
    {
        if(plateau->piece[x+1][y].orientation != orientation)
            return 0;
    }
    if(orientation == droite)
    {
        if(plateau->piece[x-1][y].orientation != orientation)
            return 0;
    }

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

    piece_siam* piececours = plateau_obtenir_piece(plateau,x,y);

    if(poussee_etre_valide(plateau,x,y,orientation))
    {
        if(orientation==haut)
        {
            y1=y+longueur;
            //if(y1==NBR_CASES && plateau->piece[x][NBR_CASES-1].type==rocher)
            //{
            //    coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            //}
            while( y1>=y )
            {
                if(y1 <= (NBR_CASES -1))
                {
                    piececours = plateau_obtenir_piece(plateau,x,y1-1);
                    piece_definir(&(plateau->piece[x][y1]), piececours->type, piececours->orientation);
                }
                y1--;
            }
            piece_definir(&(plateau->piece[x][y-1]), case_vide, aucune_orientation);
        }
        if(orientation==bas)
        {
            y1=y-longueur;
            //if(y1==0 && plateau->piece[x][0].type==rocher)
            //{
            //    coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            //}
            while( y1<=y )
            {
                if(y1 >= 0)
                {
                    piececours = plateau_obtenir_piece(plateau,x,y1+1);
                    piece_definir(&(plateau->piece[x][y1]), piececours->type, piececours->orientation);
                }
                y1++;
            }
            piece_definir(&(plateau->piece[x][y+1]), case_vide, aucune_orientation);
        }
        if(orientation==gauche)
        {
            x1=x-longueur;
            //if(x1==0 && plateau->piece[0][y].type==rocher)
            //{
            //    coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            //}
            while( x1<=x )
            {
                if(x1 >= 0)
                {
                    piececours = plateau_obtenir_piece(plateau,x1+1,y);
                    piece_definir(&(plateau->piece[x1][y]), piececours->type, piececours->orientation);
                }
                x1++;
            }
            piece_definir(&(plateau->piece[x+1][y]), case_vide, aucune_orientation);
        }

        if(orientation==droite)
        {
            x1=x+longueur;
            //if(x1==NBR_CASES-1 && plateau->piece[NBR_CASES-1][y].type==rocher)
            //{
            //    coup->condition_victoire.victoire=1;
                //trouver première piece ayant participe a la poussee en partant du rocher pour joueur gagnant
            //}
            while( x1>=x )
            {
                if(x1 <= (NBR_CASES-1) ) // on ne definit que si c'est dans le plateau
                {
                    piececours = plateau_obtenir_piece(plateau,x1-1,y);
                    piece_definir(&(plateau->piece[x1][y]), piececours->type, piececours->orientation);
                }
                x1--;
            }
            piece_definir(&(plateau->piece[x-1][y]), case_vide, aucune_orientation);
        }

    }
}

int poussee_calculer_longueur(plateau_siam* plateau, int x, int y, orientation_deplacement orientation)
{
    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));
    assert(piece_etre_integre(&(plateau->piece[x][y]) ) );
    assert(orientation_etre_integre_deplacement(orientation));

    piece_siam* piece = plateau_obtenir_piece(plateau,x,y);
    int longueur = 0;
    int force = 1;

    while( ((piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1)) && force>=1 )
    {
        if(orientation == haut)
        {
                if(piece->orientation == bas)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;

                if(y == NBR_CASES-1) // si on est au limite du plateau
                    return longueur; // on ne cherche pas a aller plus loin

                y++;
                longueur++;
                piece = plateau_obtenir_piece(plateau,x,y);
        }

        if(orientation == bas)
        {
                if(piece->orientation == haut)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;

                if(y == 0) // si on est au limite du plateau
                    return longueur; // on ne cherche pas a aller plus loin

                y--;
                longueur++;
                piece = plateau_obtenir_piece(plateau,x,y);
        }

        if(orientation == gauche)
        {
                if(piece->orientation == droite)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;

                if(x == 0) // si on est au limite du plateau
                    return longueur; // on ne cherche pas a aller plus loin

                x--;
                longueur++;
                piece = plateau_obtenir_piece(plateau,x,y);
        }

        if(orientation == droite)
        {
                if(piece->orientation == gauche)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;

                if(x == NBR_CASES-1) // si on est au limite du plateau
                    return longueur; // on ne cherche pas a aller plus loin

                x++;
                longueur++;
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


    while( ((piece_etre_animal(piece)==1) || (piece_etre_rocher(piece) == 1)) && force>=1 )
    {
        if(orientation == haut)
        {
                if(piece->orientation == bas)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;
                if(piece_etre_rocher(piece) == 1)
                    cptrocher = cptrocher +1;

                if(y == NBR_CASES-1) // si on est au limite du plateau
                    return force; // on ne cherche pas a aller plus loin

                y++;
                piece = plateau_obtenir_piece(plateau,x,y);
        }

        if(orientation == bas)
        {
                if(piece->orientation == haut)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;
                if(piece_etre_rocher(piece) == 1)
                    cptrocher = cptrocher +1;

                if(y == 0) // si on est au limite du plateau
                    return force; // on ne cherche pas a aller plus loin

                y--;
                piece = plateau_obtenir_piece(plateau,x,y);
        }

        if(orientation == gauche)
        {
                if(piece->orientation == droite)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;
                if(piece_etre_rocher(piece) == 1)
                    cptrocher = cptrocher +1;

                if(x == 0) // si on est au limite du plateau
                    return force; // on ne cherche pas a aller plus loin

                x--;
                piece = plateau_obtenir_piece(plateau,x,y);
        }

        if(orientation == droite)
        {
                if(piece->orientation == gauche)
                    force = force -1;

                if(piece->orientation == orientation)
                    force = force +1;
                if(piece_etre_rocher(piece) == 1)
                    cptrocher = cptrocher +1;

                if(x == NBR_CASES-1) // si on est au limite du plateau
                    return force; // on ne cherche pas a aller plus loin

                x++;
                piece = plateau_obtenir_piece(plateau,x,y);
        }
    }



    if(force < cptrocher)
        force = 0;

    return force;

}
