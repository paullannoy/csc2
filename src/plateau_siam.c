#include "plateau_siam.h"
#include "entree_sortie.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



void plateau_initialiser(plateau_siam* plateau)
{
    // Initialise l'ensemble des cases du plateau a piece_vide
    // sauf les 3 cases du milieu avec un rocher (1,2), (2,2) et (3,2)
    //
    // L'etat de l'echiquier initial est le suivant:
    //
    // [4] *** | *** | *** | *** | *** |
    // [3] *** | *** | *** | *** | *** |
    // [2] *** | RRR | RRR | RRR | *** |
    // [1] *** | *** | *** | *** | *** |
    // [0] *** | *** | *** | *** | *** |
    //     [0]   [1]   [2]   [3]   [4]
    //


    int kx=0;
    for(kx=0 ; kx<NBR_CASES ; ++kx)
    {
        int ky=0;
        for(ky=0 ; ky<NBR_CASES ; ++ky)
        {
            piece_siam* piece=plateau_obtenir_piece(plateau,kx,ky);
            assert(piece!=NULL);

            if(ky==2 && (kx>=1 && kx<=3) )
                piece_definir_rocher(piece);
            else
                piece_definir_case_vide(piece);
        }
    }
    piece_definir(&plateau->piece[1][1], elephant, gauche);
    piece_definir(&plateau->piece[4][3], rhinoceros, haut);

    assert(plateau_etre_integre(plateau));
}

int plateau_etre_integre(const plateau_siam* plateau)
{
    assert(plateau != NULL);

    int cptRocher = 0; // initialisation compteur de rocher
    int cptElephant = 0; // initialisation compteur elephant
    int cptRhino = 0; // initialisation compteur rhinoceros
    int res = 1; // variable resultat retourne par la fonction

    int kx=0; // initialisation compteur de coordonnée x
    for(kx=0 ; kx<NBR_CASES ; ++kx)
    {
        int ky=0; // initialisation compteur de coordonnée y
        for(ky=0 ; ky<NBR_CASES ; ++ky)
        {

            if(piece_etre_integre(plateau_obtenir_piece_info(plateau,kx,ky)) != 1) // verifier que la piece est integre
            {
                res =0; // si elle n'est pas integre, arret et retour 0
                return res;
            }

            if(plateau_obtenir_piece_info(plateau,kx,ky)->type == rhinoceros) // si la piece est de type rhino
                cptRhino++; // incrementation du type rhino
            else if(plateau_obtenir_piece_info(plateau,kx,ky)->type == elephant) // incrementation du type elephant
                cptElephant++;
            else if(plateau_obtenir_piece_info(plateau,kx,ky)->type == rocher) // incrementation du type rocher
                cptRocher++;
        }
    }

    if(cptRhino > 5) // si le nombre de rhino depasse 5, plateau non integre
        res =0;
    if(cptElephant > 5) // si le nombre d'elephants depasse 5, plateau non integre
        res =0;
    if(cptRocher > 3) // si le nombre de rochers depasse 3, plateau non integre
        res =0;

    return res;
}

void test_plateau_etre_integre(void)
{
    puts("Test plateau_etre_integre \n");
    plateau_siam* plateau = malloc(sizeof(plateau_siam));
    plateau_initialiser(plateau);

    plateau_afficher(plateau);
    if(plateau_etre_integre(plateau) != 1)
        puts("Plateau init KO");

    piece_definir(&(plateau->piece[1][1]), haut , elephant );
    plateau_afficher(plateau);
    if(plateau_etre_integre(plateau) != 1)
        puts("Plateau  elephant [1][1] KO");

    piece_definir(&(plateau->piece[4][3]), bas , rhinoceros );
    plateau_afficher(plateau);
    if(plateau_etre_integre(plateau) != 1)
        puts("Plateau  elephant [4][3] KO");

    piece_definir(&(plateau->piece[0][0]), bas , rhinoceros );
    piece_definir(&(plateau->piece[0][1]), bas , rhinoceros );
    piece_definir(&(plateau->piece[0][2]), bas , rhinoceros );
    piece_definir(&(plateau->piece[0][3]), bas , rhinoceros );
    piece_definir(&(plateau->piece[0][4]), bas , rhinoceros );
    plateau_afficher(plateau);
    if(plateau_etre_integre(plateau) != 0)
        puts("Plateau  elephant [4][3] KO");
}

piece_siam* plateau_obtenir_piece(plateau_siam* plateau,int x,int y)
{
    assert(plateau != NULL); // verification plateau valide
    assert(coordonnees_etre_dans_plateau(x,y)); // verification coordonne dans le plateau valide

    piece_siam * piece = NULL; // initialisation d'une piece (pointeur)
    piece = &(plateau->piece[x][y]); // on assigne l'adresse de la piece sur la piece au coordonnée x y dans le plateau

    return piece; // on retourne cette piece
}


const piece_siam* plateau_obtenir_piece_info(const plateau_siam* plateau,int x,int y)
{
    assert(plateau != NULL); // verification plateau valide
    assert(coordonnees_etre_dans_plateau(x,y)); // verification coordonne dans le plateau valide

    const piece_siam * piece = &(plateau->piece[x][y]);
    // initialisation d'une piece et on l'assigne a la piece au coordonne x et y du plateau

    return piece; // on retourne cette piece non modifiable
}


int plateau_denombrer_type(const plateau_siam* plateau,type_piece type)
{

    assert(plateau!=NULL);
    //Algorithme
    //
    // Initialiser compteur <- 0
    // Pour toutes les cases du tableau
    //  Si case courente est du type souhaite
    //      Incremente compteur
    // Renvoie compteur
    int compteur = 0;
    int kx = 0;

    for(kx=0;kx<NBR_CASES;kx++) // compteur dans les x (coordonne)
    {
        int ky = 0;
        for(ky=0;ky<NBR_CASES;ky++) // compteur dans les y (coordonne)
        {
            const piece_siam* piece = plateau_obtenir_piece_info(plateau,kx,ky);
            assert(piece!=NULL);

            if(piece->type == type)
                compteur++;
        }
    }
    return compteur;
}

int plateau_exister_piece(const plateau_siam* plateau,int x,int y)
{
    assert(plateau != NULL); //vérifie que le pointeur n'est pas nul
    assert(coordonnees_etre_dans_plateau(x,y)); //vérification coordonnées comprises dans le plateau

    if(plateau_obtenir_piece_info(plateau,x,y)->type==case_vide)
        return 0; //case vide, retour 0

    return 1; //case non vide(elephant, rhino ou rocher), retour 1
}

void test_plateau_exister_piece(void)
{
    puts("Test plateau_exister_piece \n");
    plateau_siam* plateau = malloc(sizeof(plateau_siam));
    plateau_initialiser(plateau);

    plateau_afficher(plateau);
    if(plateau_exister_piece(plateau,2,2) != 1)
        puts("Plateau rocher 2 2 KO");

    piece_definir(&(plateau->piece[1][1]), haut , elephant );
    plateau_afficher(plateau);
    if(plateau_exister_piece(plateau,1,1) != 1)
        puts("Plateau  elephant [1][1] KO");

    piece_definir(&(plateau->piece[4][3]), bas , rhinoceros );
    plateau_afficher(plateau);
    if(plateau_exister_piece(plateau,4,3) != 1)
        puts("Plateau  elephant [4][3] KO");
}

void plateau_afficher(const plateau_siam* plateau)
{
    assert(plateau!=NULL);

    //utilisation d'une fonction generique d'affichage
    // le parametre stdout permet d'indiquer que l'affichage
    // est realise sur la ligne de commande par defaut.
    entree_sortie_ecrire_plateau_pointeur_fichier(stdout,plateau);

}
