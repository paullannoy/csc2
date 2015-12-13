#include "api_siam.h"
#include "plateau_modification.h"
#include "joueur.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

coup_jeu api_siam_tenter_introduire_nouvelle_piece_si_possible(jeu_siam* jeu,
                                                               int x,int y,
                                                               orientation_deplacement orientation)
{
    assert(jeu != NULL); // verification pointeur non nul
    assert(jeu_etre_integre(jeu));

    plateau_siam* plateau=&(jeu->plateau); // initialisation pointeur sur le plateau du jeu
    coup_jeu coup; // declaration coup du jeu
    coup_jeu_initialiser(&coup); // initialisation coup du jeu

    type_piece typejoueur = joueur_obtenir_animal(jeu->joueur); // recupere le type que le joueur doit jouer

    if(plateau_modification_introduire_piece_etre_possible(plateau,x,y,typejoueur,orientation) == 1)
    {
        plateau_modification_introduire_piece(plateau,x,y,typejoueur, orientation);
        coup.valide = 1;
        joueur_changer(&(jeu->joueur));
    }

    else
    {
        coup.valide = 0;
    }

    return coup;
}



coup_jeu api_siam_tenter_deplacer_piece_si_possible(jeu_siam* jeu,
                                                    int x,int y,
                                                    orientation_deplacement deplacement,
                                                    orientation_deplacement orientation)
{
    assert(jeu != NULL); // verification pointeur non nul
    assert(jeu_etre_integre(jeu));

    plateau_siam* plateau=&(jeu->plateau); // initialisation pointeur sur le plateau du jeu
    coup_jeu coup; // declaration coup du jeu
    coup_jeu_initialiser(&coup); // initialisation coup du jeu
    coup.valide = 0;
    //type_piece typejoueur = jeu_obtenir_type_animal_courant(jeu);

    if(plateau_modification_deplacer_piece_etre_possible(plateau,x,y,deplacement,orientation) == 1)
    {

        if(joueur_etre_type_animal(jeu->joueur, plateau_obtenir_piece_info(plateau,x,y)->type ) == 1 )
        {
            plateau_modification_deplacer_piece(plateau,x,y,deplacement, orientation);
            coup.valide = 1;
            joueur_changer(&(jeu->joueur));
        }

    }

    coordonnees_appliquer_deplacement(&x,&y,deplacement); // applique deplacement pour piece de poussee

    /*if(poussee_etre_valide(plateau,x,y,deplacement) && (deplacement==orientation) )
    {
        poussee_realiser(plateau,x,y,deplacement,typejoueur,&coup);
        plateau->piece[x][y].orientation = orientation;
        coup.valide = 1;
        joueur_changer(&(jeu->joueur));
    }*/

    return coup;
}



coup_jeu api_siam_tenter_changer_orientation_piece_si_possible(jeu_siam* jeu,int x,int y,orientation_deplacement orientation)
{
    assert(jeu != NULL); // verification pointeur non nul
    assert(jeu_etre_integre(jeu));

    plateau_siam* plateau=&(jeu->plateau); // initialisation pointeur sur le plateau du jeu
    coup_jeu coup; // declaration coup du jeu
    coup_jeu_initialiser(&coup); // initialisation coup du jeu

    type_piece typejoueur = joueur_obtenir_animal(jeu->joueur); // recupere le type que le joueur doit jouer
    const piece_siam* piece = plateau_obtenir_piece_info(&(jeu->plateau),x,y); // recupere le type de la piece aux coordonnee indiqués

    if(plateau_modification_changer_orientation_piece_etre_possible(plateau,x,y,orientation)==1 && typejoueur==piece->type )
        //si modification orientation possible ET que type jouable par joueur egale au type de la piece indiquee
    {
            plateau_modification_changer_orientation_piece(plateau,x,y,orientation); //modifie l'orientation de la pièce pour l'orientation souhaitee
            coup.valide=1; //indique la validite du coup
            joueur_changer(&(jeu->joueur));
    }
    else
    {
        coup.valide=0; // la modification de l'orientation n'est pas possible, le coup n'est pas valide
    }

    // A MODIFIER POUR AVOIR COUP VICTOIRE

    return coup;
}
