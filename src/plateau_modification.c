#include "plateau_modification.h"
#include "coordonnees_plateau.h"


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



int plateau_modification_introduire_piece_etre_possible(const plateau_siam* plateau,
                                                        int x,int y,
                                                        type_piece type,
                                                        orientation_deplacement orientation)
{

    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));

    const piece_siam* piece = plateau_obtenir_piece_info(plateau,x,y);

    if( (coordonnees_etre_bordure_plateau(x,y) == 1) && (piece_etre_case_vide(piece) == 1) )
    {
        return 1;
    }

    return 0;
}

void test_plateau_modification_introduire_piece_etre_possible(void)
{
    plateau_siam* plateau=malloc(sizeof(plateau_siam));
    plateau_initialiser(plateau);

    printf("test_plateau_modification_introduire_piece_etre_possible\n");
    piece_definir(&(plateau->piece[0][0]),elephant,haut);
    if(plateau_modification_introduire_piece_etre_possible(plateau,0,0,rhinoceros,bas)!=0)
        printf("KO introduction sur piece existante");
    if(plateau_modification_introduire_piece_etre_possible(plateau,1,1,rhinoceros,bas)!=0)
        printf("KO introduction milieu plateau case vide");
    if(plateau_modification_introduire_piece_etre_possible(plateau,NBR_CASES-1,0,rhinoceros,bas)!=1)
        printf("KO introduction sur sur case vide bordure");


}


void plateau_modification_introduire_piece(plateau_siam* plateau,
                                           int x,int y,
                                           type_piece type,
                                           orientation_deplacement orientation)
{
    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));
    assert(coordonnees_etre_bordure_plateau(x,y));
    assert(orientation_etre_integre_deplacement(orientation));
    assert(plateau_modification_introduire_piece_etre_possible(plateau,x,y,type,orientation));

    plateau->piece[x][y].type=type;
    plateau->piece[x][y].orientation=orientation;

    assert(piece_etre_animal(&(plateau->piece[x][y])));
    assert(plateau_etre_integre(plateau));

}

void test_plateau_modification_introduire_piece(void)
{
    //test fait sur API pour une pièce intègre. Ici tentative d'introduction d'un rocher puis d'une pièce non intègre. (Le programme doit planter)
    plateau_siam* plateau=malloc(sizeof(plateau_siam));
    plateau_initialiser(plateau);
    //plateau_modification_introduire_piece(plateau,0,0,rocher,haut); //piece non intègre dans piece_etre_animal -> OK
    plateau_modification_introduire_piece(plateau,0,0,elephant,haut);
    plateau_modification_introduire_piece(plateau,0,1,elephant,haut);
    plateau_modification_introduire_piece(plateau,0,2,elephant,haut);
    plateau_modification_introduire_piece(plateau,0,3,elephant,haut);
    plateau_modification_introduire_piece(plateau,0,4,elephant,haut);
    plateau_modification_introduire_piece(plateau,NBR_CASES-1,0,elephant,haut); //introduction de 6 elephants-> plateau non intègre->OK
    //plateau_modification_introduire_piece(plateau,0,0,rhinoceros,aucune_orientation); //orientation non integre->OK

}

int plateau_modification_changer_orientation_piece_etre_possible(const plateau_siam* plateau,int x0,int y0,orientation_deplacement orientation)
{
    assert(plateau != NULL); //verification pointeur plateau non nul
    assert(plateau_etre_integre(plateau));


    const piece_siam *piece = plateau_obtenir_piece_info(plateau,x0,y0);//initialisation piece a tester
    if (piece_etre_animal(piece)!=1) // si la piece n'est pas un animal on retourne 0, orientation on modifiable
        return 0;
    if(orientation==(piece->orientation)) // si l'orientation est la meme, retour 0
        return 0;

    return 1;
}





void plateau_modification_changer_orientation_piece(plateau_siam* plateau,int x0,int y0,orientation_deplacement orientation)
{
    assert(plateau != NULL); //verification pointeur plateau non nul
    assert(plateau_etre_integre(plateau));
    assert(orientation_etre_integre(orientation)); //verification integrite orientation
    assert(plateau_modification_changer_orientation_piece_etre_possible(plateau,x0,y0,orientation));

    piece_siam *piece = plateau_obtenir_piece(plateau,x0,y0);//initialisation piece a modifier
    assert(piece_etre_animal(piece));

    piece->orientation = orientation; // on modifie l'orientation par celle passé en paramètre
    assert(plateau_etre_integre(plateau));
}

void test_plateau_modification_changer_orientation_piece(void)
{
    //test pour une orientation integre pour un animal fait en API
    plateau_siam* plateau=malloc(sizeof(plateau_siam));
    plateau_initialiser(plateau);
    piece_definir(&(plateau->piece[0][0]),elephant,haut);
    //plateau_modification_changer_orientation_piece(plateau,0,0,aucune_orientation); //->piece non integre, donc plateau non integre OK
    plateau_modification_changer_orientation_piece(plateau,2,2,haut); //piece non animal -> rocher ok
}


int plateau_modification_deplacer_piece_etre_possible(const plateau_siam* plateau,
                                                      int x0,int y0,
                                                      orientation_deplacement direction_deplacement,
                                                      orientation_deplacement orientation)
{
    assert(plateau != NULL);
    assert(plateau_etre_integre(plateau));

    const piece_siam* piece = plateau_obtenir_piece_info(plateau,x0,y0);

    if( (x0==0 && direction_deplacement==gauche ) || (x0==(NBR_CASES-1) && direction_deplacement==droite ) || (y0==0 && direction_deplacement==bas ) || (x0==(NBR_CASES-1) && direction_deplacement==haut ) )
    { // si le deplacement fais en sorte de sortir du plateau
        return 0;
    }
    if(piece_etre_animal(piece)==1)
    {
        if(direction_deplacement==haut && piece_etre_case_vide(&(plateau->piece[x0][y0+1]))==1)
            return 1;
        if(direction_deplacement==bas && piece_etre_case_vide(&(plateau->piece[x0][y0-1]))==1)
            return 1;
        if(direction_deplacement==gauche && piece_etre_case_vide(&(plateau->piece[x0-1][y0]))==1)
            return 1;
        if(direction_deplacement==droite && piece_etre_case_vide(&(plateau->piece[x0+1][y0]))==1)
            return 1;
    }

    return 0;
}

void test_plateau_modification_deplacer_piece_etre_possible(void)
{
    plateau_siam* plateau=malloc(sizeof(plateau_siam));
    plateau_initialiser(plateau);
    piece_definir(&(plateau->piece[0][0]),elephant,haut);
    piece_definir(&(plateau->piece[1][1]),rhinoceros,haut);

    printf("\n test_plateau_modification_deplacer_piece_etre_possible \n");
    if(plateau_modification_deplacer_piece_etre_possible(plateau,2,2,haut,haut)!=0)
        printf("KO déplacement rocher");
    if(plateau_modification_deplacer_piece_etre_possible(plateau,0,0,bas,haut)!=0)
        printf("KO deplacement hors du plateau");
    if(plateau_modification_deplacer_piece_etre_possible(plateau,0,0,haut,haut)!=1)
        printf("KO deplacement possible");
    if(plateau_modification_deplacer_piece_etre_possible(plateau,1,1,haut,haut)!=0)
        printf("KO deplacement case occupee");

}

void plateau_modification_deplacer_piece(plateau_siam* plateau,
                                         int x0,int y0,
                                         orientation_deplacement direction_deplacement,
                                         orientation_deplacement orientation_final)
{
    assert(plateau != NULL); //verification pointeur plateau non nul
    assert(plateau_etre_integre(plateau));
    assert(orientation_etre_integre(orientation_final)); //verification integrite orientation
    assert(orientation_etre_integre_deplacement(direction_deplacement)); //verification integrite orientation
    assert(plateau_modification_deplacer_piece_etre_possible(plateau,x0,y0, direction_deplacement,orientation_final));

    piece_siam* piece = plateau_obtenir_piece(plateau,x0,y0);


    if(direction_deplacement == haut)
    {
        piece_definir(&(plateau->piece[x0][y0+1]),piece->type,orientation_final);
        piece_definir_case_vide(piece);
    }

    if(direction_deplacement == bas)
    {
        piece_definir(&(plateau->piece[x0][y0-1]),piece->type,orientation_final);
        piece_definir_case_vide(piece);
    }

    if(direction_deplacement == gauche)
    {
        piece_definir(&(plateau->piece[x0-1][y0]),piece->type,orientation_final);
        piece_definir_case_vide(piece);
    }

    if(direction_deplacement == droite)
    {
        piece_definir(&(plateau->piece[x0+1][y0]),piece->type,orientation_final);
        piece_definir_case_vide(piece);
    }

    assert(plateau_etre_integre(plateau));
}


