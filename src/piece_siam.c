#include "piece_siam.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void appel_test_piece_siam(void)
{
    test_piece_etre_integre();
    test_piece_etre_animal();
    test_piece_etre_rocher();
    test_piece_etre_case_vide();
    test_piece_definir();
}

int piece_etre_integre(const piece_siam* piece)
{
    assert(piece!=NULL); // securite pour avoir un pointeur valide

    int res = 0;// initialisation de ce que la fonction retourne
    if(piece->type == elephant || piece->type == rhinoceros) // si la piece est un animal
    {
        if(piece->orientation == haut || piece->orientation == bas || piece->orientation == gauche || piece->orientation == droite) // et a une orientation
            res = 1;
    }
    else if (piece->type == rocher || piece->type == case_vide) // si la piece est un rocher ou une case vide
    {
        if(piece->orientation == aucune_orientation) // et n'a pas d'orientation
            res = 1;
    }

    return res;
}

void test_piece_etre_integre(void)
{
    puts("Test piece_etre_integre \n");

    piece_siam *piece1 = malloc(sizeof(piece_siam)); // creation d'une piece

    /* CAS 1 */
    piece1->orientation = haut;
    piece1->type = elephant;
    if(piece_etre_integre(piece1) != 1)
        puts("elephant haut KO \n");

    /* CAS 2 */
    piece1->orientation = aucune_orientation;
    piece1->type = elephant;
    if(piece_etre_integre(piece1) != 0)
        puts("elephant aucune orientation KO \n");

    /* CAS 3 */
    piece1->orientation = aucune_orientation;
    piece1->type = rocher;
    if(piece_etre_integre(piece1) != 1)
        puts("rocher aucune orientation KO \n");

    /* CAS 4 */
    piece1->orientation = haut;
    piece1->type = case_vide;
    if(piece_etre_integre(piece1) != 0)
        puts("case_vide haut KO \n");

    /* CAS 5 */
    piece1->orientation = aucune_orientation;
    piece1->type = case_vide;
    if(piece_etre_integre(piece1) != 1)
        puts("case vide aucune orientation KO \n");

}

void piece_initialiser(piece_siam* piece)
{
    assert(piece!=NULL);

    piece_definir(piece,case_vide,aucune_orientation);

    assert(piece_etre_integre(piece));
}


int piece_etre_animal(const piece_siam* piece)
{
    assert(piece!=NULL); // securite d'un pointeur valable
    assert(piece_etre_integre(piece)); //necessite piece integre

    if( (piece->type==elephant) || (piece->type==rhinoceros) ) //Si le type est un animal
        return 1;

    return 0;
}

void test_piece_etre_animal(void)
{
    puts("test piece etre animal \n");

    piece_siam *piece1 = malloc(sizeof(piece_siam)); // creation d'une piece

    /* CAS 1  elephant */
    piece1->type=elephant;
    if(piece_etre_animal(piece1) != 1)
        puts("elephant KO \n");

    /* CAS 2  rhinoceros */
    piece1->type=rhinoceros;
    if(piece_etre_animal(piece1) != 1)
        puts("rhinoceros KO \n");

    /* CAS 3  rocher */
    piece1->type=rocher;
    if(piece_etre_animal(piece1) != 0)
        puts("rocher KO \n");

    /* CAS 4  case_vide */
    piece1->type=case_vide;
    if(piece_etre_animal(piece1) != 0)
        puts("case vide KO \n");
}



int piece_etre_rocher(const piece_siam* piece)
{
    assert(piece!=NULL); // securite d'un pointeur valable
    assert(piece_etre_integre(piece)); //necessite piece integre
    if (piece->type==rocher) //Si le type est un rocher, on retourne 1
            return 1;

        return 0;
}

void test_piece_etre_rocher(void)
{
    puts("test piece etre rocher \n");
    piece_siam *piece1 = malloc(sizeof(piece_siam)); // creation d'une piece
    /* CAS 1  elephant */
    piece1->type=elephant;
    if(piece_etre_rocher(piece1) != 0)
        puts("elephant KO \n");

    /* CAS 2  rhinoceros */
    piece1->type=rhinoceros;
    if(piece_etre_rocher(piece1) != 0)
        puts("rhinoceros KO \n");

    /* CAS 3  rocher */
    piece1->type=rocher;
    if(piece_etre_rocher(piece1) != 1)
        puts("rocher KO \n");

    /* CAS 4  case vide */
    piece1->type=case_vide;
    if(piece_etre_rocher(piece1) != 0)
        puts("case vide KO \n");
}

int piece_etre_case_vide(const piece_siam* piece)
{
    assert(piece!=NULL);
    assert(piece_etre_integre(piece)); //necessite piece integre
    if (piece->type==case_vide) //Si le type de la piece est une case vide, on retourne 1
            return 1;

        return 0;
}

void test_piece_etre_case_vide(void)
{
    puts("test piece etre case vide \n");
    piece_siam *piece1 = malloc(sizeof(piece_siam)); // on creer une piece

    /* CAS 1  elephant */
    piece1->type=elephant;
    if(piece_etre_case_vide(piece1) != 0)
        puts("elephant KO \n");

    /* CAS 2  rhinoceros */
    piece1->type=rhinoceros;
    if(piece_etre_case_vide(piece1) != 0)
        puts("rhinoceros KO \n");

    /* CAS 3  rocher */
    piece1->type=rocher;
    if(piece_etre_case_vide(piece1) != 0)
        puts("rocher KO \n");

    /* CAS 4  case_vide */
    piece1->type=case_vide;
    if(piece_etre_case_vide(piece1) != 1)
        puts("case vide KO \n");
}


void piece_definir(piece_siam* piece,type_piece type,orientation_deplacement orientation)
{
    assert(piece!=NULL); // securite d'un pointeur valable
    assert(type_etre_integre(type)); // securite d'un type integre
    assert(orientation_etre_integre(orientation)); // securite d'une orientation integre

    piece->type=type; // on assigne le type a la piece
    piece->orientation=orientation; // on assigne l'orientation a la piece

    assert(piece_etre_integre(piece)); // securite d'une piece integre
}

void test_piece_definir(void)
{
    puts("test piece definir \n");

    piece_siam *piece1 = malloc(sizeof(piece_siam)); // creation d'une piece

    /* CAS 1  elephant haut */
    type_piece type = elephant; // on assigne le type
    orientation_deplacement orientation = haut; // on assigne l'orientation
    piece_definir(piece1, type, orientation);
    if(piece1->orientation != haut)
        puts("piece haut KO \n");
    if(piece1->type != elephant)
        puts("piece elephant KO \n");

    /* CAS 2  rocher aucune orientation */
    type = rocher;
    orientation = aucune_orientation;
    piece_definir(piece1, type, orientation);
    if(piece1->orientation != aucune_orientation)
        puts("piece haut KO \n");
    if(piece1->type != rocher)
        puts("piece elephant KO \n");

    /* CAS 3  rhinoceros bas */
    type = rhinoceros;
    orientation = bas;
    piece_definir(piece1, type, orientation);
    if(piece1->orientation != bas)
        puts("piece bas KO \n");
    if(piece1->type != rhinoceros)
        puts("piece rhinoceros KO \n");
}


void piece_definir_rocher(piece_siam* piece)
{
    assert(piece!=NULL); // sécurité d'un pointeur valable
    // transforme la pièce en rocher (type rocher et orientation aucune_orientation)
    piece_definir(piece,rocher,aucune_orientation);
    assert(piece_etre_integre(piece)); // securite de piece integre
}

void piece_definir_case_vide(piece_siam* piece)
{
    assert(piece!=NULL); // sécurité d'un pointeur valable
    // transforme la pièce en case_vide (type case_vide et orientation aucune_orientation)
    piece_definir(piece,case_vide,aucune_orientation);
    assert(piece_etre_integre(piece));
}





orientation_deplacement piece_recuperer_orientation_animal(const piece_siam* piece)
{
    assert(piece!=NULL);
    assert(piece_etre_integre(piece));
    assert(piece_etre_animal(piece));

    return piece->orientation;
}


void piece_afficher(const piece_siam* piece)
{
    assert(piece!=NULL);

    printf("%s,%s",type_nommer(piece->type),orientation_nommer(piece->orientation));
}

void piece_afficher_nom_cours(const piece_siam* piece)
{
    assert(piece!=NULL);

    printf("%s",type_nommer_nom_cours(piece->type));
    if(piece_etre_animal(piece))
        printf("-%s",orientation_nommer_nom_cours(piece->orientation));
}


piece_siam piece_correspondre_nom_cours(const char* nom_cours)
{
    assert(nom_cours!=NULL);
    assert(strlen(nom_cours)==3);

    //Possibilites:
    //
    // - nom vaut "***" -> case vide
    // - nom vaut "RRR" -> rocher
    // - nom commence par "e-" ou "r-"
    //     Alors il s'agit d'un animal.
    //     -> Recuperer le 3eme caractere
    //     -> Le convertir dans l'orientation de l'animal.
    //  - Si aucun des cas precedent, alors affiche erreur.

    piece_siam piece;
    piece_initialiser(&piece);


    if(strncmp(nom_cours,"***",3)==0)
    {
        piece_definir_case_vide(&piece);
    }
    else if(strncmp(nom_cours,"RRR",3)==0)
    {
        piece_definir_rocher(&piece);
    }
    else if((nom_cours[0]=='e' || nom_cours[0]=='r') && nom_cours[1]=='-')
    {
        const type_piece type=type_correspondre_caractere_animal(nom_cours[0]);
        const orientation_deplacement orientation=orientation_correspondre_caractere(nom_cours[2]);

        piece_definir(&piece,type,orientation);
    }
    else
    {
        printf("Erreur fonction %s\n",__FUNCTION__);
        abort();
    }

    return piece;

}
