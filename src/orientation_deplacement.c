#include "orientation_deplacement.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void appel_test_orientation_deplacement(void)
{
    test_orientation_etre_integre();
    test_orientation_etre_integre_deplacement();
    test_orientation_inverser();
    test_orientation_correspondre_caractere();
}

int orientation_etre_integre(orientation_deplacement orientation)
{
    // L'enumeration designe une orientation integre si elle est compris
    //  entre 0 et 5.
    // Une enumeration etant un type non signee, il est forcement positif.
    // Il suffit donc que type soit < 5 pour designer un type valide.

    if(orientation<5)
        return 1;
    return 0;
}

void test_orientation_etre_integre(void)
{
    puts("Test orientation_etre_integrer \n");
    int i = 0;
    /*Test pour les valeurs de 0 a 4, correspondant aux 5 valeurs pouvant être prise par l'orientation*/
    for(i=0;i<5;i++)
        if(orientation_etre_integre(i) != 1)
            printf("%d KO \n",i);
    /*Test pour des valeurs de 5 à 99, ne correspondant à aucune valeur possible pour l'orientation*/
     for(i=5;i<100;i++)
         if(orientation_etre_integre(i) != 0)
             printf("%d KO \n",i);

}

int orientation_etre_integre_deplacement(orientation_deplacement direction_deplacement)
{
    assert ( orientation_etre_integre(direction_deplacement) ); // on test que la variable direction_deplacement est possible

    if (direction_deplacement == aucune_orientation ) // la variable ne correspond pas a un mouvement
            return 0;
    else // la variable correspond a un mouvement
            return 1;
}

void test_orientation_etre_integre_deplacement(void)
{
    puts("Test orientation_etre_integre_deplacement \n");

    /*Cas 1 gauche*/
    if(orientation_etre_integre_deplacement(gauche) != 1)
        puts("gauche KO \n");

    /*Cas 2 droite*/
    if(orientation_etre_integre_deplacement(droite) != 1)
        puts("droite KO \n");

    /*Cas 3 bas*/
    if(orientation_etre_integre_deplacement(bas) != 1)
        puts("bas KO \n");

    /*Cas 4 haut*/
    if(orientation_etre_integre_deplacement(haut) != 1)
        puts("haut KO \n");

    /*Cas 5 aucune_orientation*/
    if(orientation_etre_integre_deplacement(aucune_orientation) != 0)
        puts("aucune orientation KO \n");
    //if(orientation_etre_integre_deplacement(5) != 0) // assert
        //puts("aucune orientation KO \n");


}

const char* orientation_nommer(orientation_deplacement orientation)
{
    // "Look up table" (LUT) convertissant une orientation vers
    //    la chaine de caractere correspondante.

    switch(orientation)
    {
    case haut:
        return "haut"; break;
    case bas:
        return "bas"; break;
    case gauche:
        return "gauche"; break;
    case droite:
        return "droite"; break;
    case aucune_orientation:
        return "aucune"; break;
    default:
        printf("Erreur, orientation piece %d non reconnue",orientation);
        abort();
    }

    puts("Ne devrait jamais entrer sur cette ligne");
    abort();
}


const char* orientation_nommer_nom_cours(orientation_deplacement orientation)
{
    // "Look up table" (LUT) convertissant une orientation vers
    //    la chaine de caractere courte correspondante.

    switch(orientation)
    {
    case haut:
        return "^"; break;
    case bas:
        return "v"; break;
    case gauche:
        return "<"; break;
    case droite:
        return ">"; break;
    case aucune_orientation:
        return "????"; break;
    default:
        printf("Erreur, orientation piece %d non reconnue",orientation);
        abort();
    }

    puts("Ne devrait jamais entrer sur cette ligne");
    abort();
}

orientation_deplacement orientation_inverser(orientation_deplacement orientation)
{
    assert(orientation_etre_integre_deplacement(orientation));

    // "Look up table" (LUT) convertissant une orientation vers
    //    son oppose
    // haut   <-> bas
    // droite <-> gauche


    switch(orientation)
    {
    case haut:
        return bas; break;
    case bas:
        return haut; break;
    case gauche:
        return droite; break;
    case droite:
        return gauche; break;
    default:
        printf("Erreur, orientation piece %d non reconnue",orientation);
        abort();
    }

    puts("Ne devrait jamais entrer sur cette ligne");
    abort();
}

void test_orientation_inverser(void)
{
    puts("Test orientation_inverser \n");
    if(orientation_inverser(haut) != bas)
        puts("haut KO");
    if(orientation_inverser(bas) != haut)
        puts("bas KO");
    if(orientation_inverser(gauche) != droite)
        puts("gauche KO");
    if(orientation_inverser(droite) != gauche)
        puts("droite KO");

}

int orientation_caractere_etre_integre(char orientation)
{
    // Verifie que le caractere correspond a un mouvement (droite > | gauche < | haut ^ | bas v )
    if(orientation=='>' || orientation=='<' || orientation=='^' || orientation=='v')
        return 1;
    else
        return 0;
}

orientation_deplacement orientation_correspondre_caractere(char orientation)
{
    assert( orientation_caractere_etre_integre(orientation) ); // on verifie que le caractere est integre sinon on arrete le programme

    orientation_deplacement type_enum = gauche; // initialise ce que la fonction va retourner

    switch(orientation)
    {
        case '>':
            type_enum = droite; break; // on assigne orientation a droite si le caractere est '>'
        case '<':
            type_enum = gauche; break; // on assigne orientation a gauche si le caractere est '<'
        case 'v':
            type_enum = bas; break; // on assigne orientation a bas si le caractere est 'v'
        case '^':
            type_enum = haut; break; // on assigne orientation a haut si le caractere est '^'
    }

    return type_enum; // retourne l'orientation
}

void test_orientation_correspondre_caractere(void)
{
    puts("Test orientation_correspondre_caractere \n");

    /* CAS 1 haut */
    if(orientation_correspondre_caractere('^') != haut)
        puts("haut KO");
    /* CAS 2 bas */
    if(orientation_correspondre_caractere('v') != bas)
        puts("bas KO");
    /* CAS 3 gauche */
    if(orientation_correspondre_caractere('<') != gauche)
        puts("gauche KO");
    /* CAS 4 droite */
    if(orientation_correspondre_caractere('>') != droite)
        puts("droite KO");
    //if(orientation_correspondre_caractere("????") != 0)
    //      puts("aucune orientation KO");
}
