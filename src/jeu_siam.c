#include "jeu_siam.h"
#include "joueur.h"

#include "entree_sortie.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int jeu_etre_integre(const jeu_siam* jeu)
{
    assert(jeu!=NULL);

    //verification du joueur integre
    const int joueur=jeu->joueur;
    if(joueur_etre_integre(joueur)==0)
        return 0;

    //verification du plateau integre
    const plateau_siam* plateau=&jeu->plateau;
    if(plateau_etre_integre(plateau)==0)
        return 0;

    return 1;
}


void jeu_initialiser(jeu_siam* jeu)
{

    assert(jeu!=NULL);

    //initialise le plateau
    //initialise le joueur

    plateau_initialiser(&jeu->plateau);
    jeu->joueur=0;
}





void jeu_changer_joueur(jeu_siam* jeu)
{
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu));

    joueur_changer(&jeu->joueur);

    assert(jeu_etre_integre(jeu));

}


int jeu_verifier_type_piece_a_modifier(const jeu_siam* jeu,int x,int y)
{
    assert(jeu != NULL); // verifie que la structure jeu est valide
    assert(jeu_etre_integre(jeu)); // integrite du jeu
    assert(coordonnees_etre_dans_plateau(x,y)); // coordonne valide, comprises dans le plateau

    const plateau_siam* plateau = &(jeu->plateau);
    const piece_siam* piece = plateau_obtenir_piece_info(plateau,x,y); // on recupere la piece grace au coordonne et au plateau du jeu

    if(joueur_etre_type_animal(jeu->joueur,piece->type) == 1) // si la piece est l'animal du joueur on peut la modifier
        return 1;

    return 0;
}

void test_jeu_verifier_type_piece_a_modifier(void)
{
puts("Test jeu_verifier_type_piece_a_modifier \n");

jeu_siam*jeu = malloc(sizeof(jeu_siam));
plateau_initialiser(&(jeu->plateau));

jeu->joueur = 0;
piece_definir(&(jeu->plateau.piece[1][1]), elephant , haut );
if(jeu_verifier_type_piece_a_modifier(jeu,1,1) != 1)
    puts("Joueur 0 Elephant 1 1 KO \n");

jeu->joueur = 1;
piece_definir(&(jeu->plateau.piece[4][2]), rhinoceros , gauche );
if(jeu_verifier_type_piece_a_modifier(jeu,4,2) != 1)
    puts("Joueur 1 Rhinoceros 4 2 KO \n");
}

void jeu_afficher(const jeu_siam* jeu)
{
    assert(jeu!=NULL);

    //utilisation d'une fonction generique avec affichage sur
    //  la ligne de commande.
    entree_sortie_ecrire_jeu_pointeur_fichier(stdout,jeu);
}



type_piece jeu_obtenir_type_animal_courant(const jeu_siam* jeu)
{
    assert(jeu != NULL); // verification pointeur non nul
    assert(jeu_etre_integre(jeu)); // verification integrite jeu

    type_piece type = joueur_obtenir_animal(jeu->joueur); // recupere le type correspondant au numero de joueur

    return type;
}

void test_jeu_obtenir_type_animal_courant(void)
{
    puts("Test jeu_obtenir_type_animal_courant \n");

    jeu_siam*jeu = malloc(sizeof(jeu_siam));
    plateau_initialiser(&(jeu->plateau));


    jeu->joueur = 0;
    if(jeu_obtenir_type_animal_courant(jeu) != elephant)
        puts("Joueur 0 Elephant KO \n");

    jeu->joueur = 1;
    if(jeu_obtenir_type_animal_courant(jeu) != rhinoceros)
        puts("Joueur 1 Rhinoceros KO \n");
}

